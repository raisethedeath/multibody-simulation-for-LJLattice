#ifndef LJFORCE_H
#define LJFORCE_H

#include "Particle.h"


Vec2 LJForce(const Particle& a, const Particle& b, const float e0, const float s0) {
    Vec2 direction = b.position - a.position;
    float distance = direction.length();

    if (distance == 0.0) return {0.0, 0.0}; // 防止除以零
    
    if (distance <= 3 *s0* pow(2, 1.0 / 6.0)) {
        double forceMagnitude = 4 * e0 * (-12.0 * pow(s0/distance, 12.0) + 6.0 * pow(s0/distance, 6.0) )/distance;
        return direction.normalized() * forceMagnitude; // 返回单位方向上的力
    }
    else{
        return {0.0, 0.0};
    }
    
    
    
}
#endif