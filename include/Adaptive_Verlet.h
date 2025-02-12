#ifndef ADAPTIVE_VERLET_H
#define ADAPTIVE_VERLET_H
#include "Particle.h"
/*
void adpaptive_verlet(std::vector<Particle>& particles ,double dt, double tolerence, double dt_min, double dt_max){
    double max_error = 0.0;
    for (auto& particle : particles) {
        //double max_error = 0.0;
        particle.error = (particle.velocity-particle.newVelocity).length()/particle.velocity.length();
        max_error = std::max(max_error, particle.error);
    }
    
        if (max_error > tolerence){
            dt = std::max(dt_min , dt/2);
        }
        else if (max_error < tolerence/4 && dt < dt_max){
            dt = std::min(dt_max, dt*2);
        }
}
*/


#endif