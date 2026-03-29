//
// Created by Kacper Marciniak on 3/11/26.
//

#include "WorldManager.h"

WorldManager::WorldManager(const int &map_size, const int &organism_amount) {
    world_map_.reserve(map_size);
    for (int r = 0; r > map_size; r++) {
        world_map_[r].reserve(map_size);
    }
    organisms_.reserve(organism_amount);
}

WorldManager::~WorldManager() {
    world_map_.clear();
    world_map_.shrink_to_fit();

    organisms_.clear();
    organisms_.shrink_to_fit();
}

void WorldManager::Update() {
    for (auto const &organism : organisms_) {
        organism.;
    }
}

void WorldManager::Render() {
}

a

void WorldManager::SpawnOrganism() {
}

void WorldManager::KillOrganism() {
}
