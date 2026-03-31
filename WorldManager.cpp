//
// Created by Kacper Marciniak on 3/11/26.
//

#include "WorldManager.h"
#include <ctime>
#include <iostream>
#include "./Animals/Wolf.h"
#include "Animals.h"
#include "Animals/Antelope.h"
#include "Animals/Fox.h"
#include "Animals/Sheep.h"
#include "Animals/Turtle.h"

WorldManager::WorldManager(const int &map_size, const int &organism_count) {
    std::srand(time(NULL));
    world_map_.reserve(map_size);
    for (int r = 0; r < map_size; r++) {
        world_map_[r].reserve(map_size);
    }

    // add organisms to the world_map
    for (int i = 0; i < organism_count; i++) {
        // for all 5 subclasses
        const int animal_num = rand() % 5;

        organisms_.push_back(SpawnAnimals(animal_num));
    }
}

WorldManager::~WorldManager() {

    for (auto organism : organisms_) {
        delete organism;
    }

    world_map_.clear();
    world_map_.shrink_to_fit();

    organisms_.clear();
    organisms_.shrink_to_fit();
}

void WorldManager::Update() {
    for (auto &organism: organisms_) {
        organism->Update();
    }
}

void WorldManager::Render() {
}

Organism *WorldManager::SpawnAnimals(const uint8_t type) {
    switch (static_cast<AnimalTypes>(type)) {
        // Wolf
        case AnimalTypes::WOLF: {
            return new Wolf(world_map_, WOLF::STR, WOLF::INIT);
        }
        // case AnimalTypes::SHEEP: {
        //     return new Sheep();
        // case AnimalTypes::FOX: {
        //     return new Fox();
        // }
        // case AnimalTypes::TURTLE: {
        //     return new Turtle();
        // }
        // case AnimalTypes::ANTELOPE: {
        //     return new Antelope();
        // }
        default: {
            std::cerr << "Unknown AnimalType" << std::endl;
        }
    }
    return nullptr;
}

void WorldManager::KillOrganism() {
}
