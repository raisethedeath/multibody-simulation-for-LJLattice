#ifndef CONSTRAIN_H
#define CONSTRAIN_H

#include "Particle.h"


void constrainParticles(std::vector<Particle>& particles, double ri) {
    for (auto& particle : particles) {
        //float distanceSquared = particle.position.x * particle.position.x + particle.position.y * particle.position.y;

        // Inner the boundary 
        if (particle.position.length() < ri ) {
            Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
            particle.position = direction * ri; // 将粒子移动到内半径的边界上
            
        }
        
        // if (particle.position.length()<=ro+0.07 && particle.position.length()>ro){
        //     Vec2 direction = particle.position.normalized(); // 计算出粒子当前位置的单位方向
        //     particle.position = direction * ro; // 将粒子移动到内半径的边界上
        // }
        // if (particle.position.length() >ro+0.07){
        //     continue;
        // }
        
        
        
    }
}
#endif