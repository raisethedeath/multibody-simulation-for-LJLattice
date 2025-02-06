#ifndef PARTICLE_H
#define PARTICLE_H
#include "Vec2.h"


class Particle {
public:
    Vec2 position;         // 当前的位置
    Vec2 previousPosition; // 上一个位置
    Vec2 acceleration;     // 当前加速度
    Vec2 velocity;
    float mass;
    

    
    Particle(Vec2 pos, Vec2 prevPos, float m) 
        : position(pos), previousPosition(prevPos), mass(m), acceleration({0.0, 0.0}), velocity({0.0,0.0}){}
    
    void applyForce(const Vec2& force) {
        acceleration += force * (1.0f / mass); // 计算加速度
    }

    void update(float dt) {
        // 使用 Verlet 方法更新位置
        Vec2 newPosition = position*2 - previousPosition-acceleration*(-pow(dt,2));
        
        // 更新上一个位置和当前位置信息
        previousPosition = position;
        position = newPosition;
        velocity = (position-previousPosition)*(1.0/dt);

        // 重置加速度
        acceleration = {0, 0};
    }
};
#endif 