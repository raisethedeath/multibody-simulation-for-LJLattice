#ifndef NEIGHBOR_LIST_H
#define NEIGHBOR_LIST_H
#include "Particle.h"

// 更新邻居列表
std::vector<std::vector<int>> updateNeighborList(const std::vector<Particle>& particles, float cutoffRadius,float dr) {
    size_t numParticles = particles.size();
    std::vector<std::vector<int>> neighborList;
    neighborList.clear();
    neighborList.resize(numParticles);

    for (size_t i = 0; i < numParticles; ++i) {
        const Particle& a = particles[i];
        
        for (size_t j = 0; j < numParticles; ++j) {
            if (i == j) continue; // 跳过自身
            
            const Particle& b = particles[j];
            Vec2 direction = b.position - a.position;
            float distance = direction.length();

            if (distance <= (cutoffRadius+dr)) {
                neighborList[i].push_back(j); // 添加到邻居列表
            }
        }
    }
    return neighborList;
}

#endif