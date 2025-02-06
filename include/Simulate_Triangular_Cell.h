#ifndef SIMULATE_TRIANGULAR_CELL_H
#define SIMULATE_TRIANGULAR_CELL_H

#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
#include "Neighbor_List.h"
#include <unordered_map>
#include <utility> // for std::pair>
#include <boost\functional\hash.hpp>
#include "Grid.h"



void simulate_triangular_cell(std::vector<Particle>& particles, Energy& energy, float dt, const float e0, const float s0, 
                                   float ro, float ri, std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid) {
    
    float cutoffRadius = 3*pow(2, 1.0/6.0) * s0;
    size_t numParticles = particles.size();
    //float CELL_SIZE = cutoffRadius;

    // 清空所有粒子的加速度
    for (auto& particle : particles) {
        particle.acceleration = {0.0, 0.0}; // 重置加速度
    }

    // 重置能量值
    energy.reset(); // 确保能量在每次模拟时都从零开始

    

    // 创建网格以进行粒子划分
    //std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;

    // 将粒子放入网格
    grid.clear();
    for (size_t i = 0; i < numParticles; ++i) {
        auto gridIndex = std::make_pair(static_cast<int>(floor(particles[i].position.x / cutoffRadius)), 
                                         static_cast<int>(floor(particles[i].position.y / cutoffRadius)));
        grid[gridIndex].push_back(i);
    }

    // 定义相邻单元格的偏移量
    std::vector<std::pair<int, int>> neighborOffsets = {
        {0, 0},
        {-1, -1}, 
        {-1, 0},  
        {-1, 1},  
        {0, -1},  
        {0, 1},   
        {1, -1},  
        {1, 0},   
        {1, 1}    
    };

    // 计算粒子之间的引力
    for (const auto& cell : grid) {
        const auto& particleIndices = cell.second;

        for (size_t i = 0; i < particleIndices.size(); ++i) {

            int indexA = particleIndices[i];
            energy.totalEk += Ek(particles[indexA]); // 计算并累加动
        
            
                             

            // 考虑邻近单元格的粒子
            for (const auto& offset : neighborOffsets) {
                auto neighborIndex = std::make_pair(cell.first.first + offset.first, cell.first.second + offset.second);
                
                // 检查邻居单元格是否存在
                if (grid.find(neighborIndex) != grid.end()) {
                    const auto& neighborParticleIndices = grid[neighborIndex];

                    // 计算与邻近单元格内粒子的相互作用
                    for (int indexB : neighborParticleIndices) {
                        if (indexB <= indexA) continue; // 跳过自身

                        Vec2 force = LJForce(particles[indexA], particles[indexB], e0, s0);

                        if (particles[indexA].position.length() < ro && particles[indexB].position.length() < ro ) {
                            particles[indexA].applyForce(force);
                            particles[indexB].applyForce(-force);
                            energy.totalEp +=Ep1(particles[indexA], particles[indexB], e0, s0);
                        } 
                        else if (particles[indexA].position.length() < ro) {
                            particles[indexA].applyForce(force); 
                            energy.totalEp += Ep1(particles[indexA], particles[indexB], e0, s0);
                        }
                        else if(particles[indexB].position.length() < ro){
                            particles[indexB].applyForce(-force);
                            energy.totalEp += Ep1(particles[indexA], particles[indexB], e0, s0);
                        }
                        else {
                            continue;
                        }
                    }
                }
            }
        //energy.totalEk += Ek(particles[indexA]); 
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
        //energy.totalEk += Ek(particle); 
    }
}

#endif
