//
// Created by Kacper Marciniak on 3/11/26.
//

#include "WorldManager.h"
#include <ctime>
#include <iostream>
#include "./Animals/Wolf.h"
#include "Animals.h"

WorldManager::WorldManager(const int &map_size, const int &organism_count) {
    std::srand(time(NULL));
    world_map_.reserve(map_size);
    for (int r = 0; r < map_size; r++) {
        world_map_[r].reserve(map_size);
    }

    for (int i = 0; i < organism_count; i++) {
        // for all 10 subclasses
        auto random_num = rand() % 10;

        organisms_.push_back(SpawnOrganism(random_num));
    }
}

WorldManager::~WorldManager() {
    world_map_.clear();
    world_map_.shrink_to_fit();

    organisms_.clear();
    organisms_.shrink_to_fit();
}

void WorldManager::Update() {
    for (auto &organism: organisms_) {
        organism.Update();
    }
}

void WorldManager::Render() {
}

Organism *WorldManager::SpawnOrganism(const uint8_t type) {
    switch (static_cast<AnimalTypes>(type)) {
        // Wolf
        case AnimalTypes::WOLF: {
            return new Wolf::Wolf();
        }
        case AnimalTypes::SHEEP: {
            return new Sheep();
            case AnimalTypes::FOX: {
                return new Fox();
            }
            case AnimalTypes::TURTLE: {
                return new Turtle();
            }
            case AnimalTypes::ANTELOPE: {
                return new Antelope();
            }
            default: ;
            std::cerr << "Unknown AnimalType" << std::endl;
        }
    }
}
    void WorldManager::KillOrganism()
    {
    }
