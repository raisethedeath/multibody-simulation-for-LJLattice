#ifndef ENERGY_H
#define ENERGY_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

class Energy {
public:
    double totalEp; // 总势能
    double totalEk; // 总动能

    Energy() : totalEp(0.0f), totalEk(0.0f) {} // 初始化

    void reset() {
        // 重置能量值
        totalEp = 0.0;
        totalEk = 0.0;
    }
};

double Ep1(const Particle& a, const Particle& b, const double e0, const double s0){
    double distance = (a.position- b.position).length();
    if (distance == 0) return {0}; // 防止除以零
    
    if (distance <= 3 *s0* pow(2, 1.0 / 6.0)) {
        double Ep1 = 4 * e0 * (pow(s0/distance, 12.0)  - pow(s0/distance, 6.0) );
        return Ep1;
    }
 
    return {0}; // 超出范围返回零力
}
/*
float Ep2(const Particle& a,const float k0,const float ri, const float ro){
    if (a.position.length()<ri){
        return 0.5*k0*pow(a.position.length()-ri,2);
    }
    
    
    return 0;
}
*/



float Ep_t(std::vector<Particle>& particles, std::vector<Particle> particles0, const double e0, const double s0, const double ro){
    int numParticles = particles.size();
    double Ep_t = 0.0;
    for (size_t i = 0; i < numParticles; ++i) {
        for (size_t j = i + 1; j < numParticles; ++j) {  
            if (particles0[i].position.length()>=ro && particles0[j].position.length()>=ro )
            {
                continue;
            }
                     
            else{
                Ep_t += Ep1(particles[i], particles[j], e0, s0);
            }   

            
        }
    }
    return Ep_t;
}

double Ek(const Particle& a){
    double Ek = 0.5* a.mass*a.velocity.length()*a.velocity.length();
    return Ek;
}
double Ek_t(std::vector<Particle>& particles){
    int numParticles = particles.size();
    double Ek_t =0.0;
    for (size_t i = 0; i<numParticles; ++i){
        Ek_t += Ek(particles[i]);
    }
    return Ek_t;
    
}

void E_t(std::vector<Particle>& particles,  Energy& energy, const float e0, const float s0, const float ro){
    int numParticles = particles.size();
    double Ep_t = 0.0;
    double Ek_t = 0.0;
    for (size_t i = 0; i < numParticles; ++i) {
        Ek_t += Ek(particles[i]);
        for (size_t j = i + 1; j < numParticles; ++j) {           
                if (particles[i].state==false && particles[j].state==false )
            {
                continue;
            }
                     
            else{
                Ep_t += Ep1(particles[i], particles[j], e0, s0);
            }
    
        }
    }
    energy.totalEp = Ep_t;
    energy.totalEk =Ek_t;
}

#endif 