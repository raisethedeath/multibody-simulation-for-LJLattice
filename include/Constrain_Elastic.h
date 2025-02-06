#ifndef CONSTRAIN_ELASTIC_J
#define CONSTRAIN_ELASTIC_J

#include "Particle.h"

Vec2 constrainParticlesElastic(const Particle& a, float ri,float k0) {
   
        float distanceSquared = a.position.x * a.position.x + a.position.y * a.position.y;

        // 如果粒子进入内外半径，则反弹
        if (distanceSquared < ri * ri) {
            Vec2 direction = a.position.normalized(); 
            
            return direction*(ri-a.position.length())*k0;
            
        }
        else{
            return {0,0};
        }
       
            
        
    
}

#endif