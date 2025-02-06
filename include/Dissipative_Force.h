#ifndef DISSIPATIVE_FORCE_H
#define DISSIPATIVE_FORCE_H

#include "Particle.h"


Vec2 DissipativeForce(const Particle& a, const float k) {
    Vec2 f_d_1 = -a.velocity*k;
    return f_d_1;
    
}
#endif