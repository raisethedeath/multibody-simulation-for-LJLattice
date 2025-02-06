#ifndef GRID_H
#define GRID_H
#include "Neighbor_List.h"
#include <unordered_map>
#include <utility> // for std::pair>
#include <boost\functional\hash.hpp>

class Cell{
    public:
    std::unordered_map<std::pair<int, int>, std::vector<int>, boost::hash<std::pair<int, int>>> grid;
};

#endif