#include "Vec2.h"
#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
#include "Save.h"
#include "Simulate_Triangular.h"
#include "Triangular_Distribution.h"
#include "Constrain.h"
#include "Constrain_Elastic.h"


int main() {
    int rows = 100;       // 行数
    int cols = 100;       // 列数
    const double ri0 = 5.0;     // 内半径
    double ro = 15.0;    // 外半径
    double distance = 1.0; // 粒子之间的距离
    double e0 = 1.0;     // 势能深度
    double s0 = distance*pow(2.0,-1.0/6.0);     // 交互作用的特征长度
    

    double m =1.0;

    double t0 = distance*pow(m/e0,0.5);
    double v0 = pow(e0/m,0.5);
    double k0 = 1e3*2*e0/pow(distance,2);
    double k_1= pow(m*e0,0.50)/distance;
    double total_t = 10.0*t0;
    //内边界的运动方式
    // 简谐运动
    double ri = ri0;
    const double A = 0.10f; 
    double w = 4*3.1415/t0;
    //匀速膨胀
    const double v = v0; 


    

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro,m);
    std::string folderPath = "Data/pendulum/"; // 指定文件夹
    std::string fileName = folderPath + "A=0.1,w=2,ri=5,ro=15,t=10,t_interval=0.05,dt=0.0001.csv "; 

    Energy energy; // 创建 Energy 实例

    for (auto& particle :particles){
        particle.fix_state(ro);
    }

    // 模拟参数
    double dt = 0.0001*t0;
    //double steps = total_t/dt;
    double t = 0.0;
    double t_total = 10.0*t0;
    double intervals = 0.1*t0; //保存数据的时间间隔
    double t_interval = -dt;
    //int num_intervals = intervals/dt;


    

    for (t;t<=t_total;t+=dt) {
        
            ri = ri0 +A- A*std::cos(w*t);
            //simulate_triangular(particles,energy, dt, e0, s0,ro,ri,k0);
            constrainParticles(particles, ri);
            simulate_triangular(particles,energy, dt, e0, s0,ro,ri);
       

        //simulate_triangular(particles,energy, dt, e0, s0,ro,ri);
        // 约束粒子位置，不让其进入内半径
        //constrainParticles(particles, ri,ro);
        // 数据保存
        if ( t>= t_interval ) {
            t_interval+= intervals;
            energy.reset();
            E_t(particles,  energy, e0,s0, ro);
            saveToCSV(particles, energy,t ,fileName, t!=0.0);
        }
    }

    std::cout << "模拟完成，粒子数据已保存至 LJ1.csv" << std::endl;

    return 0;
}