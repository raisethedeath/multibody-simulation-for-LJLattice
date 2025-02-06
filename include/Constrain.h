#ifndef CONSTRAIN_H
#define CONSTRAIN_H

#include "Particle.h"


void constrainParticles(std::vector<Particle>& particles, float ri,float ro) {
    for (auto& particle : particles) {
        float distanceSquared = particle.position.x * particle.position.x + particle.position.y * particle.position.y;

        // 如果粒子进入内外半径，则反弹
        if (distanceSquared < ri * ri) {
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ri; // 将粒子移动到内半径的边界上
            // 对速度反转
            //particle.velocity.x = -particle.velocity.x;
            //particle.velocity.y = -particle.velocity.y;
        }
        
        if (distanceSquared<=pow(ro+0.05,2) && distanceSquared>pow(ro,2)){
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ro; // 将粒子移动到内半径的边界上
        }
        if (distanceSquared >pow(ro+0.05,2)){
            continue;
        }
        
        
        
    }
}
#endif