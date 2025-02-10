#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"
#include <algorithm>


class Particle {
public:
    Vec2 position;         // 当前的位置
    Vec2 previousPosition; // 上一个位置
    Vec2 acceleration;     // 当前加速度
    Vec2 velocity;
    //Vec2 newVelocity; 
    //double error;
    double mass;
    bool state;

    
    Particle(Vec2 pos, Vec2 prevPos, double m) 
        : position(pos), previousPosition(prevPos), mass(m), acceleration({0.0, 0.0}), velocity({0.0,0.0}){}
    
    void applyForce(const Vec2& force) {
        acceleration += force * (1.0f / mass); // 计算加速度
    }

    void update(double dt) {
        // 使用 Verlet 方法更新位置
        //error = 0.0;
        Vec2 newPosition = position*2 - previousPosition-acceleration*(-dt*dt);
        
        // 更新上一个位置和当前位置信息
        previousPosition = position;
        position = newPosition;
        //velocity += acceleration*dt;
        velocity = (position-previousPosition)*(1.0/dt);
        
        
        // 重置加速度
        acceleration = {0.0, 0.0};
    }
    
    void fix_state (double ro){
        if (position.length() >= ro){
            state = false;
        }
        else {
            state = true;
        }
    }
    
};
#endif 