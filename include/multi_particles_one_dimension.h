#ifndef MUTI_PARTICLES_ONEDIMENSION_H
#define MUTI_PARTICLES_ONEDIMENSION_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

std::vector<Particle> generateMultiParticles(float number,float distance, float v0, float dt) {
    std::vector<Particle> particles;
    for (int n=0; n<number;++n){
        Vec2 p1;
        if (n==0){
            //p1.x = -3*distance;
            p1.x= 0.0;
            p1.y = 0.0;
        }
        else{
            p1.x = n*distance;
            p1.y = 0;
        }
       
        Vec2 p2;
        if (n==0){
            p2.x = -3*distance+v0*dt;
            p2.y = 0;
        }
        
        else{
            p2.x = n*distance;
            p2.y = 0;
        }
        particles.emplace_back(p1,p1, 1.0f); // 创建粒子对象并添加到列表
    }
    
    return particles;
}
#endif