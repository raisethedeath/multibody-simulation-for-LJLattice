#ifndef TRIANGULAR_H
#define TRIANGULAR_H

#include "Particle.h"


// 生成三角晶格分布的粒子
std::vector<Particle> generateTriangularLattice(int rows, int cols, double distance, double ri, double ro, double m) {
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
            if (p.x*p.x + p.y*p.y >= ri*ri && p.x*p.x + p.y*p.y <= (ro+3)*(ro+3)) {
                particles.emplace_back(p,p,m); // 创建粒子对象并添加到列表
            }
        }
       
        }
        return particles;  
    }
#endif