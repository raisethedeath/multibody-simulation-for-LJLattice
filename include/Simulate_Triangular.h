#ifndef SIMULATE_Triangular_H
#define SIMULATE_Triangular_H

#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
#include "Dissipative_Force.h"
#include "Constrain_Elastic.h"


void simulate_triangular(std::vector<Particle>& particles, Energy& energy, double dt, const double e0, const double s0, double ro, double ri) {
    size_t numParticles = particles.size();
    
    // 清空所有粒子的加速度
    for (auto& particle : particles) {
        particle.acceleration = {0, 0}; // 重置加速度
    }

    // 重置能量值
    //energy.reset(); // 确保能量在每次模拟时都从零开始

    // 计算粒子之间的引力
    for (size_t i = 0; i < numParticles; ++i) {
        
        //energy.totalEk += Ek(particles[i]); // 计算并累加动能
        //Vec2 f_d_i = DissipativeForce(particles[i],k);
        //Vec2 Fk = constrainParticlesElastic(particles[i],ri,k0);
        for (size_t j = i + 1; j < numParticles; ++j) {
            //Vec2 f_d_j = DissipativeForce(particles[j],k);
            Vec2 force = LJForce(particles[i], particles[j], e0, s0);
            //Vec2 Fki = constrainParticlesElastic(particles[i],ri,k0);
            //Vec2 Fkj = constrainParticlesElastic(particles[j],ri,k0);
            //energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            
            if (particles[i].state && particles[j].state) {
                particles[i].applyForce(force );
                particles[j].applyForce(-force ); // 反向作用力
                //energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            } else if (particles[i].state) {
                particles[i].applyForce(force);
                //energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            } else if (particles[j].state) {
                particles[j].applyForce(-force);
                //energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            }
            
           
            
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
    }


}



#endif