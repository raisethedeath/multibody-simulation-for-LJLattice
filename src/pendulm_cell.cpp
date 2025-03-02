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
    const double ri0 = 5.0;     // 内半径
    double ro = 20.0;    // 外半径
    double distance = 1.0; // 粒子之间的距离
    double e0 = 1.0;     // 势能深度
    double s0 = distance*pow(2.0,-1.0/6.0);     // 交互作用的特征长度
    

    double m =1.0;

    double t0 = distance*pow(m/e0,0.5);
    double v0 = pow(e0/m,0.5);
    double k0 = 1e4;
    //double k_1= pow(m*e0,0.50)/distance;
    double total_t = 10.0*t0;
    //内边界的运动方式
    // 简谐运动
    double ri = ri0;
    const double A = 0.2; 
    double w = 2*3.1416/t0;
    //匀速膨胀
    const double v = v0; 
    
    double kf = 0.0;


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro,m);
    //std::vector<Particle> particles0 = particles;
    std::string folderPath = "D:/Research Data/Data/pendulum/"; // 指定文件夹
    std::string fileName = folderPath + "Cell,pendulum,A=0.2,w=2,ri=5,ro=20,t=10,t_interval=0.10,dt=0.0001.csv "; 
    std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;

    Energy energy; // 创建 Energy 实例

    //double max_delta_pos = 0.0;

    for (auto& particle :particles){
        particle.fix_state(ro);
    }

    // 模拟参数
    double dt = 0.0001*t0;
    //double steps = total_t/dt;
    double t_interval = -dt;
    double t = 0.0;
    double intervals = 0.1*t0; //保存数据的时间间隔
    double T_interval = -dt;
    double Intervals = 2.0*t0;
    //int num_intervals = intervals/dt;
    double lambda = kf*dt/m;


    

    for (t; t <= total_t; t+=dt) {
        
            ri = ri0 +A- A*std::cos(w*t);
            //simulate_triangular(particles,energy, dt, e0, s0,ro,ri,k0);
            //constrainParticles(particles, ri);
            simulate_triangular_cell(particles, energy, dt, e0, s0,k0,lambda,ro,ri,grid);
       

        //simulate_triangular(particles,energy, dt, e0, s0,ro,ri);
        // 约束粒子位置，不让其进入内半径
        //constrainParticles(particles, ri,ro);
         // Save Data
         //Save the simulation result
         if ( t>= t_interval ) {
            t_interval+= intervals;
            energy.reset();
            E_t(particles,  energy, e0,s0, ri,ro, k0);
            saveToCSV(particles, energy,t ,fileName, t!=0.0);
        }
        // Save the max delta x for each step
        if ( t>= T_interval ) {
            T_interval+= Intervals;
            std::cout << "Time:" << t << " max displacement:" << energy.max_delta_pos << std::endl;
        }
    }
    DWORD end = GetTickCount();  
    std::cout << "程序运行时间: " << (end - start)/60000 << " min" << std::endl; 

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}