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
    //float k0 = e0/pow(distance,2.0);

    double m =1.0;
    //double tolerence = 0.001;
    //double dt_min = 0.00001;
    //double dt_max = 0.001;

    double t0 = 1.0;
    //float v0 = pow(e0/m,0.5);
    double v0 = 1.0;

    double total_t = 10.0*t0;
    //内边界的运动方式
    // 简谐运动
    double ri = ri0;
    const float A = 0.8*ri0; 
    double w = 3.1416;
    //匀速膨胀
    const double v =10* v0; 
    double k0 = 1e4;


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, distance, ri, ro,m);
    //std::vector<Particle> particles = particles0;
    std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;
    std::string folderPath = "D:/Research Data/Data/energy_conservation/"; // 指定文件夹
    //std::string fileName = folderPath + "Cell-test2,v=1v0,t=0.5,ri=5,ro=15,t_t=5,dt=0.0001.csv "; 
    //std::string fileName = folderPath + "test, cell, static, constrain, t_interval=0.01,dt=0.0001,ri=5,ro=15,t_total=2.csv ";
    std::string fileName = folderPath + "relaxation, cell,ri=5,ro=20,dt=0.00005,ti=1,v=10,t_tot=10,interval=0.01.csv";  
    
    Energy energy; // 创建 Energy 实例

    for (auto& particle :particles){
        particle.fix_state(ro);
    }

    // 模拟参数
    double dt = 0.00005*t0;
    double ti = 1*t0;
    double t = 0.0;
    double intervals = 0.01*t0; //保存数据的时间间隔
    //int num_intervals = intervals/dt;
    double t_interval = 0.0;

    

    for (t; t <= total_t+dt; t+=dt) {
        //ri = ri0+A*  std::sin(w * step*dt);
        
        //ri = ri0 + v0*dt*step;
        //ri=ri0;
        
        if (t<= ti){
            ri = ri0 + v*t;
            //constrainParticles(particles, ri);
            simulate_triangular_cell(particles, energy, dt, e0, s0,k0,ro,ri,grid);
            //constrainParticles(particles, ri,ro);
            
        }
        if (t > ti){
            //double ri = 7.0;
            //constrainParticles(particles, ri);
            ri = 15.0;
            simulate_triangular_cell(particles,  energy, dt,  e0, s0,k0,ro,15.0,grid);
            
        }
        
        
        

        // 数据保存
        if ( t>= t_interval ) {
            t_interval+= intervals;
            energy.reset();
            E_t(particles,  energy, e0,s0, ri,ro,k0);
            saveToCSV(particles, energy,t ,fileName, t!=0.0);
        }
    }
    DWORD end = GetTickCount();  
    std::cout << "程序运行时间: " << (end - start)/60000 << " min" << std::endl; 

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}