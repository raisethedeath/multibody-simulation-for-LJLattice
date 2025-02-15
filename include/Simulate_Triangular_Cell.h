#ifndef SIMULATE_TRIANGULAR_CELL_H
#define SIMULATE_TRIANGULAR_CELL_H

#include "Particle.h"
#include "Energy.h"
#include "LJForce.h"
//#include "Neighbor_List.h"
#include "Constrain_Elastic.h"
#include <unordered_map>
#include <utility> // for std::pair>
#include <boost\functional\hash.hpp>
//#include "Adaptive_Verlet.h"
//#include "Grid.h"



void simulate_triangular_cell(std::vector<Particle>& particles,  Energy& energy, double dt, const double e0, const double s0, double k0,
                                   double ro, double ri, std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid) {
    
    double cutoffRadius = 3.0*pow(2, 1.0/6.0) * s0;
    size_t numParticles = particles.size();
    //float CELL_SIZE = cutoffRadius;

    // 清空所有粒子的加速度
    for (auto& particle : particles) {
        particle.acceleration = {0.0, 0.0}; // 重置加速度
    }

    // 重置能量值
    //energy.reset(); // 确保能量在每次模拟时都从零开始

    

    // 创建网格以进行粒子划分
    //std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;

    // 将粒子放入网格
    grid.clear();
    for (size_t i = 0; i < numParticles; ++i) {
        auto gridIndex = std::make_pair(static_cast<int>(round(particles[i].position.x / cutoffRadius)), 
                                         static_cast<int>(round(particles[i].position.y / cutoffRadius)));
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
            //energy.totalEk += Ek(particles[indexA]); // 计算并累加动
            //仅对区域内的粒子计算半径，避免重复计算
            if (particles[indexA].state){
                particles[indexA].radius = particles[indexA].position.length();
            }
            
            //particles[indexA].radius = particles[indexA].position.length();
            
                             

            // 考虑邻近单元格的粒子
            for (const auto& offset : neighborOffsets) {
                auto neighborIndex = std::make_pair(cell.first.first + offset.first, cell.first.second + offset.second);
                
                // 检查邻居单元格是否存在
                if (grid.find(neighborIndex) != grid.end()) {
                    const auto& neighborParticleIndices = grid[neighborIndex];

                    // 计算与邻近单元格内粒子的相互作用
                    for (int indexB : neighborParticleIndices) {
                        if (indexB <= indexA) continue; // 跳过自身

                        //Vec2 force = LJForce(particles[indexA], particles[indexB], e0, s0);
                        if (particles[indexB].state){
                            particles[indexB].radius = particles[indexB].position.length();
                        }
                        //particles[indexB].radius = particles[indexB].position.length();
                        if (particles[indexA].state && particles[indexB].state ) {
                            Vec2 force = LJForce(particles[indexA], particles[indexB], e0, s0);
                            Vec2 ela_forceA =-constrainParticlesElastic(particles[indexA],ri,k0);
                            Vec2 ela_forceB =-constrainParticlesElastic(particles[indexB],ri,k0);
                            particles[indexA].applyForce(force-ela_forceA);
                            particles[indexB].applyForce(-force-ela_forceB);
                            //energy.totalEp +=Ep1(particles[indexA], particles[indexB], e0, s0);
                        } 
                        else if (particles[indexA].state) {
                            Vec2 force = LJForce(particles[indexA], particles[indexB], e0, s0);
                            Vec2 ela_forceA =-constrainParticlesElastic(particles[indexA],ri,k0);
                            particles[indexA].applyForce(force-ela_forceA); 
                            //energy.totalEp += Ep1(particles[indexA], particles[indexB], e0, s0);
                        }
                        else if(particles[indexB].state){
                            Vec2 force = LJForce(particles[indexA], particles[indexB], e0, s0);
                            Vec2 ela_forceB =-constrainParticlesElastic(particles[indexB],ri,k0);
                            particles[indexB].applyForce(-force-ela_forceB);
                            //energy.totalEp += Ep1(particles[indexA], particles[indexB], e0, s0);
                        }
                        else {
                            continue;
                        }
                    }
                }
            }
        
        }
    }

    // 更新粒子位置
    for (auto& particle : particles) {
        particle.update(dt);
    }
    //adpaptive_verlet(particles, dt,tolerence, dt_min, dt_max);
}

#endif
