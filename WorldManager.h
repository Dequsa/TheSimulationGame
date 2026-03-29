//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_WORLDMANAGER_H
#define C__1_WORLDMANAGER_H
#pragma once
#include "organism.h"


class WorldManager {
private:
    std::vector<Organism> organisms_;
    std::vector<std::vector<char>> world_map_;
public:
    WorldManager(const int &map_size, const int &organism_amount);
    ~WorldManager();
    void Update();
    void Render();
    void SpawnOrganism();
    void KillOrganism();
};


#endif //C__1_WORLDMANAGER_H