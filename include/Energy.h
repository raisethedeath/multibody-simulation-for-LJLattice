#ifndef ENERGY_H
#define ENERGY_H

#include "Particle.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

class Energy {
public:
    float totalEp; // 总势能
    float totalEk; // 总动能

    Energy() : totalEp(0.0f), totalEk(0.0f) {} // 初始化

    void reset() {
        // 重置能量值
        totalEp = 0.0f;
        totalEk = 0.0f;
    }
};

float Ep1(const Particle& a, const Particle& b, const float e0, const float s0){
    float distance = (a.position- b.position).length();
    if (distance == 0) return {0}; // 防止除以零
    
    if (distance <= 3 *s0* pow(2, 1.0 / 6.0)) {
        float Ep1 = 4 * e0 * (pow(s0/distance, 12.0)  - pow(s0/distance, 6.0) );
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

float Ek(const Particle& a){
    float Ek = 0.5* a.mass*a.velocity.length()*a.velocity.length();
    return Ek;
}

#endif 