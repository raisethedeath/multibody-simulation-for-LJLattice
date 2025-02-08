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
    const double ri0 = 5.0f;     // 内半径
    double ro = 10.0f;    // 外半径
    double distance = 1.0f; // 粒子之间的距离
    double e0 = 1.0f;     // 势能深度
    double s0 = distance*pow(2.0,-1.0/6.0);     // 交互作用的特征长度
    //float k0 = e0/pow(distance,2.0);

    double m =1.0;
    //double tolerence = 0.001;
    //double dt_min = 0.00001;
    //double dt_max = 0.001;

    double t0 = 1.0;
    //float v0 = pow(e0/m,0.5);
    double v0 = 1.0;

    double total_t = 5.0*t0;
    //内边界的运动方式
    // 简谐运动
   double ri = ri0;
    const float A = 0.8*ri0; 
    double w = 3.1416;
    //匀速膨胀
    const double v =1* v0; 


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, distance, ri, ro,m);
    std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;
    std::string folderPath = "Data/energy_conservation/"; // 指定文件夹
    //std::string fileName = folderPath + "Cell-test2,v=1v0,t=0.5,ri=5,ro=15,t_t=5,dt=0.0001.csv "; 
    //std::string fileName = folderPath + "test, cell, static, constrain, t_interval=0.01,dt=0.0001,ri=5,ro=15,t_total=2.csv ";
    std::string fileName = folderPath + "conservation, adaptive ,cell,ri=5,ro=10,dt=0.0001,t=0.5,v=0.5,t_tot=5,interval=0.1.csv";  
    
    Energy energy; // 创建 Energy 实例

    // 模拟参数
    double dt = 0.0005*t0;
    double ti = 0.5*t0;
    double t = 0.0;
    double intervals = 0.1*t0; //保存数据的时间间隔
    //int num_intervals = intervals/dt;
    double t_interval = -dt;

    

    for (t; t <= total_t; t+=dt) {
        //ri = ri0+A*  std::sin(w * step*dt);
        
        //ri = ri0 + v0*dt*step;
        //ri=ri0;
        
        if (t<= ti){
            ri = ri0 + v*t;
            constrainParticles(particles, ri,ro);
            simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,grid);
            //constrainParticles(particles, ri,ro);
            
        }
        if (t > ti){
            simulate_triangular_cell(particles,energy, dt,  e0, s0,ro,ri,grid);
            
        }
        //adpaptive_verlet(particles, dt, tolerence, dt_min, dt_max);
        
       /*
        ri = ri0 + v*dt*step;
        constrainParticles(particles, ri,ro);
        simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,k0,grid);
       */
        
        
        /*
        simulate_triangular_cell(particles,energy, dt, e0, s0,ro,ri,k0,grid);
        // 约束粒子位置，不让其进入内半径
        constrainParticles(particles, ri0,ro);
        */
        
        

        // 数据保存
        if ( t>= t_interval ) {
            t_interval+= intervals;
            energy.reset();
            E_t(particles, energy, e0,s0, ro);
            saveToCSV(particles, energy,t ,fileName, t!=0.0);
        }
    }
    DWORD end = GetTickCount();  
    std::cout << "程序运行时间: " << (end - start)/60000 << " min" << std::endl; 

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}