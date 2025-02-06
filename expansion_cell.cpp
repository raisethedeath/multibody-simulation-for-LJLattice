#include "Vec2.h"
#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
#include "Save.h"
#include "Simulate_Triangular_Cell.h"
#include "Triangular_Distribution.h"
#include "Constrain.h"
#include <windows.h>

int main() {
    DWORD start = GetTickCount(); 

    int rows = 100;       // 行数
    int cols = 100;       // 列数
    const float ri0 = 5.0f;     // 内半径
    float ro = 20.0f;    // 外半径
    float distance = 1.0f; // 粒子之间的距离
    float e0 = 1.0f;     // 势能深度
    float s0 = distance*pow(2,-1.0/6.0);     // 交互作用的特征长度
    float k0 = e0/pow(distance,2.0);

    float m =1.0;

    float t0 = 1.0;
    float v0 = pow(e0/m,0.5);

    float total_t = 10.0*t0;
    //内边界的运动方式
    // 简谐运动
    float ri = ri0;
    const float A = 0.8*ri0; 
    float w = 3.1416;
    //匀速膨胀
    const float v =0.2* v0; 


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, distance, ri, ro);
    std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;
    std::string folderPath = "Data/expansion/"; // 指定文件夹
    //std::string fileName = folderPath + "Cell-test2,v=1v0,t=0.5,ri=5,ro=15,t_t=5,dt=0.0001.csv "; 
    //std::string fileName = folderPath + "test, cell, static, constrain, t_interval=0.01,dt=0.0001,ri=5,ro=15,t_total=2.csv ";
    std::string fileName = folderPath + "cell,ri=5,ro=20,v=0.2,t_tot=10,interval=0.1,dt=0.00005.csv";  
    
    Energy energy; // 创建 Energy 实例

    // 模拟参数
    float dt = 0.00005*t0;
    float steps = total_t/dt;
    //float t = 2*t0;
    float intervals = 0.1*t0; //保存数据的时间间隔
    int num_intervals = intervals/dt;


    

    for (int step = 0; step <= steps; ++step) {
        //ri = ri0+A*  std::sin(w * step*dt);
        
        //ri = ri0 + v0*dt*step;
        //ri=ri0;
        /*
        if (step<= t/dt){
            ri = ri0 + v*dt*step;
            constrainParticles(particles, ri,ro);
            simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,k0,grid);
            
        }
        if (step> t/dt){
            simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,k0,grid);
            
        }
        */
        
       
        
        ri = ri0 + v*dt*step;
        constrainParticles(particles, ri,ro);
        simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,grid);
        
        
        

        // 数据保存
        if (step % num_intervals == 0) {
            saveToCSV(particles, energy,fileName, step != 0);
        }
    }
    DWORD end = GetTickCount();  
    std::cout << "程序运行时间: " << (end - start)/1000 << " 秒" << std::endl; 

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}