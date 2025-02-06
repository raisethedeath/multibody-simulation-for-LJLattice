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

class Particle {
public:
    Vec2 position;
    Vec2 velocity;
    float mass;

    Particle(Vec2 pos, float m) : position(pos), mass(m), velocity({0, 0}) {}

    void update(float dt) {
        position += velocity * dt;
    }

    void applyForce(const Vec2& force, float dt) {
        Vec2 acceleration = force * (1.0f / mass);
        velocity += acceleration * dt; // 更新速度
    }
};

// 计算两个粒子之间的引力
Vec2 LJForce(const Particle& a, const Particle& b, const float e0, const float s0) {
    Vec2 direction = b.position - a.position;
    float distance = direction.length();

    if (distance == 0) return {0, 0}; // 防止除以零

    if (distance <= 3 *s0* pow(2,1/6)) {
        float forceMagnitude = 4 * e0 * (-12 * pow(s0, 12) / pow(distance, 13) + 6 * pow(s0, 6) / pow(distance, 7));
        return direction.normalized() * forceMagnitude; // 返回单位方向上的力
    }
  

    return {0, 0}; // 超出范围返回零力
}

void simulate(std::vector<Particle>& particles, float dt, const float e0, const float s0, float ro) {
    size_t numParticles = particles.size();

    // 清空所有粒子的力
    for (auto& particle : particles) {
        particle.velocity = {0, 0}; // 重置速度
    }

    // 计算粒子之间的引力
    for (size_t i = 0; i < numParticles; ++i) {
        for (size_t j = i + 1; j < numParticles; ++j) {
            // 计算当前两个粒子之间的距离
            //float d = (particles[i].position - particles[j].position).length(); // 假设 position 是 Vec2 类型
            Vec2 force = LJForce(particles[i], particles[j], e0, s0);
            if (particles[i].position.length()<=ro && particles[j].position.length()<=ro){
                particles[i].applyForce(force, dt);
                particles[j].applyForce(-force, dt); // 反向作用力
            }
            if (particles[i].position.length()<=ro && particles[j].position.length()>=ro){
                particles[i].applyForce(force, dt);
                particles[j].applyForce({0,0}, dt); // 反向作用力
            }
            if (particles[i].position.length()>=ro && particles[j].position.length()<=ro){
                particles[i].applyForce({0,0}, dt);
                particles[j].applyForce(-force, dt); // 反向作用力
            }
            if (particles[i].position.length()>=ro && particles[j].position.length()>=ro){
                particles[i].applyForce({0,0}, dt);
                particles[j].applyForce({0,0}, dt); // 反向作用力
            }
            
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
    }
}

// 保存数据
void saveToCSV(const std::vector<Particle>& particles, const std::string& filename, bool append = true) {
    std::ofstream file;

    // 根据 append 参数决定是打开为追加模式还是覆盖模式
    if (append) {
        file.open(filename, std::ios::app); // 以追加模式打开
    } else {
        file.open(filename); // 默认是覆盖模式
        // 写入CSV头
        file << "Step,ParticleID,PositionX,PositionY\n";
    }

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        file << i << ","
             << particles[i].position.x << ","
             << particles[i].position.y << "\n";
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
            if (pow(p.x, 2) + pow(p.y, 2) >= pow(ri, 2) && pow(p.x, 2) + pow(p.y, 2) <= pow(ro+3, 2)) {
                particles.emplace_back(p, 1.0f); // 创建粒子对象并添加到列表
            }
        }
       
        }
        return particles;  
    }
// 在模拟中约束位置
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
        /*
        if (distanceSquared >= ro * ro) {
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ri; // 将粒子移动到内半径的边界上
            particle.velocity.x = -particle.velocity.x;
            particle.velocity.y = -particle.velocity.y;
        }
        */
    }
}
   

int main() {
    int rows = 50;       // 行数
    int cols = 50;       // 列数
    const float ri0 = 5.0f;     // 内半径
    float ro = 15.0f;    // 外半径
    float distance = 1.0f; // 粒子之间的距离
    float e0 = 1.0f;     // 势能深度
    float s0 = distance*pow(2,-1/6);     // 交互作用的特征长度
    
    
    //内边界的运动方式
    // 简谐运动
    float ri = ri0;
    const float A = 0.5*ri0; 
    float w = 3.14;
    //匀速膨胀
    const float v0 = 0.5; 
    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro);

    // 模拟参数
    float dt = 0.001f;    // 时间步长
    int steps = 1500;    // 模拟步数

    // 开始模拟
    for (int step = 0; step < steps; ++step) {
        //ri = ri0+A*  std::sin(w * step*dt);
        /*
         if (step<=10000){
            ri = ri0 + v0*dt*step;
        }
        if (step>10000){
            ri = 10;
        }
        */
        ri = ri0;
        
        simulate(particles, dt, e0, s0,ro);
        // 约束粒子位置，不让其进入内半径
        constrainParticles(particles, ri,ro);
        // 每500步保存一次数据
        if (step % 50 == 0) {
            saveToCSV(particles, "1.csv", step != 0);
        }
    }

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}