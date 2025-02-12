#ifndef CONSTRAIN_ELASTIC_J
#define CONSTRAIN_ELASTIC_J

#include "Particle.h"

Vec2 constrainParticlesElastic(Particle& a, double ri,double k0) {
   
        //float distanceSquared = a.position.x * a.position.x + a.position.y * a.position.y;

        // 如果粒子进入内外半径，则反弹
        //a.radius= a.position.length();
        if (a.radius < ri) {
            //a.ela_state = false;
            Vec2 direction = a.position.normalized(); 
            
            return direction*(ri-a.radius)*k0;
            
        }
        else{
            
            return {0.0,0.0};
        }
        
       
            
        
    
}

#endif