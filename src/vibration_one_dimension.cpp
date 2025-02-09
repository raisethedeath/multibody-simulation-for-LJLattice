#include "Energy.h"
#include "Particle.h"
#include "LJForce.h"
#include "Vec2.h"
#include "Save.h"
#include "Simulate_One_Dimension.h"
#include "multi_particles_one_dimension.h"

int main() {
    float d0 = 1.0f;
    float e0 = 1.0f;     // 势能深度
    float s0 = d0*pow(2,-1/6);     // 交互作用的特征长度
    float m = 1;
    float t0 = s0*pow(m/e0,0.5);
    float v0 = pow(e0/m,0.5);

    float v = 0.5*v0;
    float total_t = 10*t0;
    float number = 2;
    float distance = 1*d0;

    float dt = 1e-4*t0;
    int steps = total_t/dt;
    float intervals = 0.1*t0; //保存数据的时间间隔
    int num_intervals = intervals/dt;


    // 生成粒子
    std::vector<Particle> particles = generateMultiParticles(number, distance, v, dt);

    std::string folderPath = "Data/vibration_one_dimension/"; // 指定文件夹
    std::string fileName = folderPath + "static,10t0,2,dt=0.0001.csv"; 
    Energy energy; // 创建 Energy 实例

    //开始模拟
    for (int step = 0; step < steps; ++step) {
        
        simulate_one_dimension(particles, energy, dt, e0, s0);

        // 数据保存
        if (step % num_intervals == 0) {
            saveToCSV(particles, energy,fileName, step != 0);
        }
    }

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}