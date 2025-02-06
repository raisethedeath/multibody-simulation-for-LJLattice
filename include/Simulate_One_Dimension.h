#ifndef SIMULATE_ONE_DIMENSION_H
#define SIMULATE_ONE_DIMENSION_H

#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"


void simulate_one_dimension(std::vector<Particle>& particles, Energy& energy, float dt, const float e0, const float s0) {
    size_t numParticles = particles.size();
    
    // 清空所有粒子的加速度
    for (auto& particle : particles) {
        particle.acceleration = {0, 0}; // 重置加速度
    }

    // 重置能量值
    energy.reset(); // 确保能量在每次模拟时都从零开始

    // 计算粒子之间的引力
    for (size_t i = 0; i < numParticles; ++i) {
        //Vec2 confineforce = confineForce(particles[i], k0, ri,ro);
        //energy.totalEp += Ep2(particles[i], ri,ro); // 计算并累加势能
        energy.totalEk += Ek(particles[i]); // 计算并累加动能

        for (size_t j = i + 1; j < numParticles; ++j) {
            Vec2 force = LJForce(particles[i], particles[j], e0, s0);

            particles[i].applyForce(force );
            particles[j].applyForce(-force ); // 反向作用力

            energy.totalEp += Ep1(particles[i], particles[j], e0, s0);
            /*
            if (particles[i].position.length() < ro && particles[j].position.length() < ro) {
                particles[i].applyForce(force );
                particles[j].applyForce(-force ); // 反向作用力
            } else if (particles[i].position.length() < ro) {
                particles[i].applyForce(force);
            } else if (particles[j].position.length() < ro) {
                particles[j].applyForce(-force );
            }
            */
            
            
           /*
           particles[i].applyForce(force - (confineforce * -1));
            particles[j].applyForce(-force - (confineforce * -1)); // 反向作用力
           */
            
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
    }


}

#endif