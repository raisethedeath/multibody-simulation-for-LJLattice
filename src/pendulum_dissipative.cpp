#include "Vec2.h"
#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
#include "Save.h"
#include "Simulate_Triangular_Dissipative.h"
#include "Triangular_Distribution.h"
#include "Constrain.h"



int main() {
    int rows = 50;       // 行数
    int cols = 50;       // 列数
    const float ri0 = 5.0f;     // 内半径
    float ro = 15.0f;    // 外半径
    float distance = 1.0f; // 粒子之间的距离
    float e0 = 1.0f;     // 势能深度
    float s0 = distance*pow(2,-1.0/6.0);     // 交互作用的特征长度
    

    float m =1.0;

    float t0 = s0*pow(m/e0,0.5);
    float v0 = pow(e0/m,0.5);
    float k0 = 1e3*2*e0/pow(s0,2);
    //float k_1= 0.001*pow(m*e0,0.50)/s0;
    float k_1= 0.005*e0/(distance*v0); 
    float total_t = 5*t0;
    //内边界的运动方式
    // 简谐运动
    float ri = ri0;
    const float A = 0.2f; 
    float w = 4*3.1416/t0;
    //匀速膨胀
    const float v = v0; 


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro);
    std::string folderPath = "Data/dissipative_pendulum/"; // 指定文件夹
    std::string fileName = folderPath + "Dissipative,k=0.001,A=0.2,w=2,ri=5,ro=15,t=1,t_interval=0.05.csv "; 

    Energy energy; // 创建 Energy 实例

    // 模拟参数
    float dt = 0.0005*t0;
    float steps = total_t/dt;
    float t = 1*t0;
    float intervals = 0.05*t0; //保存数据的时间间隔
    int num_intervals = intervals/dt;


    

    for (int step = 0; step <= steps; ++step) {
        
            ri = ri0 +A- A*std::cos(w*step*dt);
            //simulate_triangular(particles,energy, dt, e0, s0,ro,ri,k0);
            constrainParticles(particles, ri,ro);
            simulate_triangular_dissipative(particles,energy, dt, e0, s0,ro,ri,k0,k_1);
       

        //simulate_triangular(particles,energy, dt, e0, s0,ro,ri);
        // 约束粒子位置，不让其进入内半径
        //constrainParticles(particles, ri,ro);
        // 数据保存
        if (step % num_intervals == 0) {
            saveToCSV(particles, energy,fileName,step!=0);
        }
    }

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}