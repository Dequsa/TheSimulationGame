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

constexpr int MAX_TRIES = 200;

Position WorldManager::ChooseAndSetSpawnPoint() {
    const int max_x = static_cast<int>(world_map_[0].size());
    const int max_y = static_cast<int>(world_map_.size());
    int max_tries = MAX_TRIES;
    // (1 --- max_x - 1) <- range of rand so we can do the search with checking neighbors

    while (max_tries--) {
        const int r_x = 1 + rand() % (max_x - 2);
        const int r_y = 1 + rand() % (max_y - 2);

        // check random position if its empty
        if (world_map_[r_y][r_x] == '0') {
            return Position{r_x, r_y};
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (world_map_[r_y + i][r_x + j] == '0') {
                    return Position{r_x + j, r_y + i};
                }
            }
        }
    }
    return Position{-1, -1};
}

WorldManager::WorldManager(const int map_size, const int organism_count) {
    std::srand(time(NULL));
    world_map_.reserve(map_size);
    for (int r = 0; r < map_size; r++) {
        world_map_[r].reserve(map_size);
    }

    // add organisms to the world_map
    for (int i = 0; i < organism_count; i++) {
        // for all 5 subclasses
        const int animal_num = rand() % 5;

        Position spawn_pos = ChooseAndSetSpawnPoint();

        if (spawn_pos.x == -1 || spawn_pos.y == -1) {
            i--;
            continue;
        }

        organisms_.push_back(SpawnAnimals(animal_num, spawn_pos));
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
        UpdateData data = organism->Update();
        // if (data.type != AnimalTypes::NONE) {
        //
        //     SpawnAnimals(data.type, )
        // }

    }
}

void WorldManager::Render() {
}

std::unique_ptr<Organism> WorldManager::SpawnAnimals(const uint8_t type, const Position &spawn_pos) {

    switch (static_cast<AnimalTypes>(type)) {
        // Wolf
        case AnimalTypes::WOLF: {
            return std::make_unique<Wolf>(world_map_, spawn_pos);
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
