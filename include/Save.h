#ifndef SAVE_H
#define SAVE_H

#include "Particle.h"
#include "Energy.h"


void saveToCSV(const std::vector<Particle>& particles, const Energy& energy, double t, const std::string& filename, bool append = true) {
    std::ofstream file;

    // 根据 append 参数决定是打开为追加模式还是覆盖模式
    if (append) {
        file.open(filename, std::ios::app); // 以追加模式打开
    } else {
        file.open(filename); // 默认是覆盖模式
        // 写入CSV头
        file << "Step,ParticleID,PositionX,PositionY,Ek,Ep,Et,VelocityX,VelocityY\n";
    }

    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < particles.size(); ++i) {
        file << i << "," 
             << particles[i].position.x << ","
             << particles[i].position.y << ","
             << energy.totalEk << ","   
             << energy.totalEp << ","   
             << (energy.totalEk + energy.totalEp) << "," 
             << particles[i].velocity.x << ","
             << particles[i].velocity.y << ","
             <<t << "\n";
    }

    file.close();
}

#endif