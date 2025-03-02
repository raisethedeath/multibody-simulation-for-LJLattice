#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"
#include <algorithm>

/*
Verlet method and to fix the particles in the circles, determine the external particle as a state
fix the state and no force apply on it
*/
class Particle {
public:
    Vec2 position;         // 当前的位置
    Vec2 previousPosition; // 上一个位置
    Vec2 acceleration;     // 当前加速度
    Vec2 velocity;
    Vec2 delta_pos;
    //Vec2 newVelocity; 
    //double error;
    double mass;
    double radius;     //到原点的距离
    bool state;
    bool out_state;
    //bool ela_state;

    
    Particle(Vec2 pos, Vec2 prevPos, double m) 
        : position(pos), previousPosition(prevPos), mass(m), acceleration({0.0, 0.0}), velocity({0.0,0.0}){}
    
    void applyForce(const Vec2& force) {
        acceleration += force * (1.0f / mass); // 计算加速度
    }

    void update(double dt,double lambda) {
        // use verlet method to update positions
        // Introduce kf
        // lambda = kf*dt/m --> dissipative part

        Vec2 newPosition = position*(2.0-lambda) - previousPosition*(1.0-lambda)-acceleration*(-dt*dt);
        
        // 更新上一个位置和当前位置信息
        previousPosition = position;
        position = newPosition;
        delta_pos = position-previousPosition;
        //velocity += acceleration*dt;
        velocity = (delta_pos)*(1.0/dt);
        
        
        // 重置加速度
        acceleration = {0.0, 0.0};
        
    }
    
    void fix_state (double ro){
        radius = position.length();
        if (radius >= ro){
            state = false;
        }
        else {
            state = true;
        }
    }

    void change_out_state(double ro){
        if (radius >ro+5){
            out_state = true;
        }
        else {
            out_state = false;
        }
    }
    
    
};
#endif 