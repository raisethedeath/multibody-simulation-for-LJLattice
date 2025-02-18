#include "Triangular_Distribution.h"
#include "Energy.h"

int main(){
    int rows = 50;       // 行数
    int cols = 50;       // 列数
    const double ri0 = 5.0;     // 内半径
    double ro = 17.0;    // 外半径
    double distance = 1.0; // 粒子之间的距离
    double e0 = 1.0;     // 势能深度
    double s0 = distance*pow(2.0,-1.0/6.0);     // 交互作用的特征长度

    double m =1.0;

    double t0 = s0*pow(m/e0,0.5);
    double v0 = pow(e0/m,0.5);

    double total_t = 10.0*t0;
    //内边界的运动方式
    // 简谐运动
    double ri = ri0;
    const double A = 0.1; 
    double w = 2*3.1415/t0;
    //匀速膨胀
    const double v = v0; 

    // 生成粒子
    std::vector<Particle> particles = generateTriangularLattice(rows, cols, s0, ri, ro,m);
    std::string folderPath = "D:/Research Data/Data/pendulum/"; // 指定文件夹
    std::string fileName = folderPath + "1.csv"; 
   

    std::ofstream file;
    bool append = true;

    // 根据 append 参数决定是打开为追加模式还是覆盖模式
    if (append) {
        file.open(fileName, std::ios::app); // 以追加模式打开
    } else {
        file.open(fileName); // 默认是覆盖模式
        // 写入CSV头
        file << "Step,ParticleID,PositionX,PositionY,Ek,Ep,Et\n";
    }

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << fileName << std::endl;
        return 0;
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        file << i << "," // 假设 i 是步数，可以根据您的实际情况更改
             << particles[i].position.x << ","
             << particles[i].position.y << "\n";
             //<< energy.totalEk << ","   // 动能
             //<< energy.totalEp << ","   // 势能
             
             //<< (energy.totalEk + energy.totalEp) << "\n"; // 总能量
    }

    file.close();
}