//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_WORLDMANAGER_H
#define C__1_WORLDMANAGER_H
#pragma once
#include "organism.h"
#include <vector>


class WorldManager {
private:
    std::vector<std::unique_ptr<Organism>> organisms_;
    std::vector<std::vector<char>> world_map_;

    Position ChooseAndSetSpawnPoint();

public:
    WorldManager(const int map_size, const int organism_count);

    ~WorldManager();

    void Update();

    void Render();

    std::unique_ptr<Organism> SpawnAnimals(const uint8_t type, const Position &spawn_pos);

    void KillOrganism();

    const std::vector<std::vector<char>> *GetWorldMap() const { return &world_map_; }
};


#endif //C__1_WORLDMANAGER_H
