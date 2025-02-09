// 使用前记得更改存储的数据名称，防止之前计算的数据被覆盖
// matlab中对参数进行及时调整
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct Vec2 {
    float x, y;

    Vec2 operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator*(float scalar) const {
        return {x * scalar, y * scalar};
    }

    Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y};
    }
    

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2 normalized() const {
        float len = length();
        return (len > 0) ? Vec2{x / len, y / len} : Vec2{0, 0};
    }

    // 构造函数
    Vec2(float x = 0, float y = 0) : x(x), y(y) {}

    // 重载负号运算符
    Vec2 operator-() const {
        return Vec2(-x, -y);
    }
};
class Energy {
public:
    float totalEp; // 总势能
    float totalEk; // 总动能

    Energy() : totalEp(0.0f), totalEk(0.0f) {} // 初始化

    

    void reset() {
        // 重置能量值
        totalEp = 0.0f;
        totalEk = 0.0f;
    }
};

class Particle {
public:
    Vec2 position;         // 当前的位置
    Vec2 previousPosition; // 上一个位置
    Vec2 acceleration;     // 当前加速度
    Vec2 velocity;
    float mass;

    //Particle(Vec2 pos, float m) : position(pos),  previousPosition(pos),mass(m), acceleration({0, 0}) {}
    // 修改构造函数以接受初始位置和前一个位置
    Particle(Vec2 pos, Vec2 prevPos, float m) 
        : position(pos), previousPosition(prevPos), mass(m), acceleration({0, 0}), velocity({0,0}) {}
    
    void applyForce(const Vec2& force) {
        acceleration += force * (1.0f / mass); // 计算加速度
    }

    void update(float dt) {
        // 使用 Verlet 方法更新位置
        Vec2 newPosition = position*2 - previousPosition-acceleration*(-pow(dt,2));
        
        // 更新上一个位置和当前位置信息
        previousPosition = position;
        position = newPosition;
        velocity = (position-previousPosition)*(1/dt);

        // 重置加速度
        acceleration = {0, 0};
    }
};

// 计算两个粒子之间的引力
Vec2 LJForce(const Particle& a, const Particle& b, const float e0, const float s0) {
    Vec2 direction = b.position - a.position;
    float distance = direction.length();

    if (distance == 0) return {0, 0}; // 防止除以零

    if (distance <= 3 *s0* pow(2, 1.0 / 6.0)) {
        float forceMagnitude = 4 * e0 * (-12 * pow(s0, 12) / pow(distance, 13) + 6 * pow(s0, 6) / pow(distance, 7));
        return direction.normalized() * forceMagnitude; // 返回单位方向上的力
    }

    return {0, 0}; // 超出范围返回零力
}
// 约束力
/*
Vec2 confineForce(const Particle& a, const float k0, float ri,float ro){
    if (a.position.length() < (ri)){
        float confineLength = ri -  a.position.length();
        float magnitude = k0*confineLength;
        return a.position.normalized()*magnitude;
    };
    return {0,0};
    }
*/

    /*
    if (a.position.length()>ro){
        float confineL = a.position.length()-ro;
        float mag = k0*confineL;
        return -a.position.normalized()*mag;
    }
    */
    

float Ep1(const Particle& a, const Particle& b, const float e0, const float s0){
    float distance = (a.position- b.position).length();
    if (distance == 0) return {0}; // 防止除以零

    if (distance <= 3 *s0* pow(2, 1.0 / 6.0)) {
        float Ep1 = 4 * e0 * (pow(s0, 12) / pow(distance, 12) - pow(s0, 6) / pow(distance, 6));;
        return Ep1;
    }

    return {0}; // 超出范围返回零力
}
float Ep2(const Particle& a,const float k0,const float ri, const float ro){
    if (a.position.length()<ri){
        return 0.5*k0*pow(a.position.length()-ri,2);
    }
    
    
    return 0;
}
float Ek(const Particle& a){
    float Ek = 0.5* a.mass*pow(a.velocity.length(),2);
    return Ek;
}


void simulate(std::vector<Particle>& particles, Energy& energy, float dt, const float e0, const float s0, float ro, float ri, float k0) {
    size_t numParticles = particles.size();
    
    // 清空所有粒子的加速度
    for (auto& particle : particles) {
        particle.acceleration = {0, 0}; // 重置加速度
    }

    // 重置能量值
    energy.reset(); // 确保能量在每次模拟时都从零开始

    // 计算粒子之间的引力
    for (size_t i = 0; i < numParticles; ++i) {
        //Vec2 confineforce = confineForce(particles[i], k0, ri,ro);
        energy.totalEp += Ep2(particles[i], k0, ri,ro); // 计算并累加势能
        energy.totalEk += Ek(particles[i]); // 计算并累加动能

        for (size_t j = i + 1; j < numParticles; ++j) {
            Vec2 force = LJForce(particles[i], particles[j], e0, s0);
            energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            
            if (particles[i].position.length() < ro && particles[j].position.length() < ro) {
                particles[i].applyForce(force );
                particles[j].applyForce(-force ); // 反向作用力
            } else if (particles[i].position.length() < ro) {
                particles[i].applyForce(force);
            } else if (particles[j].position.length() < ro) {
                particles[j].applyForce(-force );
            }
            
           /*
           particles[i].applyForce(force - (confineforce * -1));
            particles[j].applyForce(-force - (confineforce * -1)); // 反向作用力
           */
            
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
    }


}
void constrainParticles(std::vector<Particle>& particles, float ri,float ro) {
    for (auto& particle : particles) {
        float distanceSquared = particle.position.x * particle.position.x + particle.position.y * particle.position.y;

        // 如果粒子进入内外半径，则反弹
        if (distanceSquared < ri * ri) {
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ri; // 将粒子移动到内半径的边界上
            // 对速度反转
            //particle.velocity.x = -particle.velocity.x;
            //particle.velocity.y = -particle.velocity.y;
        }
        
    }
}



// 保存数据
void saveToCSV(const std::vector<Particle>& particles, const Energy& energy, const std::string& filename, bool append = true) {
    std::ofstream file;

    // 根据 append 参数决定是打开为追加模式还是覆盖模式
    if (append) {
        file.open(filename, std::ios::app); // 以追加模式打开
    } else {
        file.open(filename); // 默认是覆盖模式
        // 写入CSV头
        file << "Step,ParticleID,PositionX,PositionY,Ek,Ep,Et\n";
    }

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        file << i << "," // 假设 i 是步数，可以根据您的实际情况更改
             << particles[i].position.x << ","
             << particles[i].position.y << ","
             << energy.totalEk << ","   // 动能
             << energy.totalEp << ","   // 势能
             << (energy.totalEk + energy.totalEp) << "\n"; // 总能量
    }

    file.close();
}

// 生成三角晶格分布的粒子
std::vector<Particle> generateTriangularLattice(int rows, int cols, float distance, float ri, float ro) {
    std::vector<Particle> particles;

    for (int col = -cols / 2; col < cols / 2; ++col) {
        for (int row=-rows/2;row<rows/2;++row){
            Vec2 p;
            p.x = col * distance; // 水平方向的距离
            p.y = row * distance * std::sqrt(3) / 2; // 垂直方向的距离
            
            // 奇数行偏移
            if (abs(row) % 2 == 1) {
                p.x += distance / 2; // 偶数行与奇数行之间的偏移
            }
            // 仅在指定半径内创建粒子
            if (pow(p.x, 2) + pow(p.y, 2) >= pow(ri-0.01, 2) && pow(p.x, 2) + pow(p.y, 2) <= pow(ro+3, 2)) {
                particles.emplace_back(p,p, 1.0f); // 创建粒子对象并添加到列表
            }
        }
       
        }
        return particles;  
    }
// 在模拟中约束位置
/*
void constrainParticles(std::vector<Particle>& particles, float ri,float ro) {
    for (auto& particle : particles) {
        float distanceSquared = particle.position.x * particle.position.x + particle.position.y * particle.position.y;

        // 如果粒子进入内外半径，则反弹
        if (distanceSquared <= ri * ri) {
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ri; // 将粒子移动到内半径的边界上
            // 对速度反转
            particle.velocity.x = -particle.velocity.x;
            particle.velocity.y = -particle.velocity.y;
        }
        
        
    }
}
*/

   

int main() {
    int rows = 50;       // 行数
    int cols = 50;       // 列数
    const float ri0 = 5.0f;     // 内半径
    float ro = 10.0f;    // 外半径
    float distance = 1.0f; // 粒子之间的距离
    float e0 = 1.0f;     // 势能深度
    float s0 = distance*pow(2,-1/6);     // 交互作用的特征长度
    float k0 = 1e3;
    
    //内边界的运动方式
    // 简谐运动
    float ri = ri0;
    const float A = 0.8*ri0; 
    float w = 3.14;
    //匀速膨胀
    const float v0 = 0.0; 
    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro);
    Energy energy; // 创建 Energy 实例

    // 模拟参数
    float dt = 0.001f;    // 时间步长
    int steps = 80;    // 模拟步数

    // 开始模拟
    /*
    for (int step = 0; step < steps; ++step) {
        //ri = ri0+A*  std::sin(w * step*dt);
        if (step<=10000){
            ri = ri0 + v0*dt*step;
        }
        if (step>10000){
            ri = 10;
        }
    */
    for (int step = 0; step < steps; ++step) {
        //ri = ri0+A*  std::sin(w * step*dt);
        
        ri = ri0 + v0*dt*step;
        //ri=ri0;
        simulate(particles,energy, dt, e0, s0,ro,ri,k0);
        // 约束粒子位置，不让其进入内半径
        //constrainParticles(particles, ri,ro);
        // 数据保存
        if (step % 1 == 0) {
            saveToCSV(particles, energy,"try3.csv", step != 0);
        }
    }

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}