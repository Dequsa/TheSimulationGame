//
// Created by Kacper Marciniak on 3/11/26.
//

#include "WorldManager.h"
#include <ctime>
#include <iostream>
#include <algorithm>
#include "./Animals/Wolf.h"
#include "Animals.h"
#include "Animals/Antelope.h"
#include "Animals/Fox.h"
#include "Animals/Sheep.h"
#include "Animals/Turtle.h"

constexpr int MAX_TRIES = 200;

WorldManager::WorldManager(const int map_size, const int organism_count) : world_map_(
    map_size, std::vector<char>(map_size, '#')) {
    std::srand(time(NULL));
    // add organisms to the world_map
    for (int i = 0; i < organism_count; i++) {
        // for all 5 subclasses
        // const int animal_num = rand() % static_cast<int>(OrganismTypes::NONE);

        Position spawn_pos = ChooseAndSetSpawnPoint();

        if (spawn_pos.x == -1 || spawn_pos.y == -1) {
            i--;
            continue;
        }

        auto animal_num = static_cast<int>(OrganismTypes::WOLF);
        organisms_.push_back(SpawnAnimals(static_cast<OrganismTypes>(animal_num), spawn_pos));
    }
}

WorldManager::~WorldManager() {
    world_map_.clear();
    world_map_.shrink_to_fit();

    organisms_.clear();
    organisms_.shrink_to_fit();
}

void WorldManager::SortOrganisms() {
    std::sort(organisms_.begin(), organisms_.end(),
              [](const std::unique_ptr<Organism> &a, const std::unique_ptr<Organism> &b) {
                  return a->GetInit() > b->GetInit();
              });
}


std::vector<int> WorldManager::GetOrganismIdsAtPositions(const std::vector<Position>& positions) const {
    std::vector<int> ids;
    for (int i = 0; i < organisms_.size(); i++) {
        for (const auto& pos : positions) {
            if (organisms_[i]->GetPosition() == pos) {
                ids.push_back(i);
                break;
            }
        }
        if (ids.size() == positions.size()) break;
    }
    return ids;
}

Position WorldManager::ChooseAndSetSpawnPoint() const {
    const int max_x = static_cast<int>(world_map_[0].size());
    const int max_y = static_cast<int>(world_map_.size());
    int max_tries = MAX_TRIES;
    // (1 --- max_x - 1) <- range of rand so we can do the search with checking neighbors

    while (max_tries--) {
        const int r_x = 1 + rand() % (max_x - 2);
        const int r_y = 1 + rand() % (max_y - 2);

        // check random position if its empty
        if (world_map_[r_y][r_x] == MapSprites::EMPTY) {
            return Position{r_x, r_y};
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (world_map_[r_y + i][r_x + j] == MapSprites::EMPTY) {
                    return Position{r_x + j, r_y + i};
                }
            }
        }
    }
    return Position{-1, -1};
}

Position WorldManager::GetChildSpawnPosition(const std::vector<Position> &positions) const {
    for (const auto [x, y]: positions) {
        for (int k = -1; k < 2; k++) {
            for (int i = -1; i < 2; i++) {
                const Position c_pos = {k + x, i + y};
                if (c_pos.x < 0 || c_pos.y < 0) {
                    continue;
                }
                if (world_map_[c_pos.y][c_pos.x] == '#') {
                    return c_pos;
                }
            }
        }
    }
    return {-1, -1};
}

int WorldManager::CreateFight(const std::vector<Position> &positions) {
    for (const auto [x, y]: positions) {
        if (x == -1 || y == -1) {
            std::cerr << "Error while creating a fight at pos: " << x << ' ' << y << '\n';
            return -1;
        }
    }

    //TODO DO THIS
    const std::vector<int> ids = GetOrganismIdsAtPositions(positions);

    if (ids.size() < 2) {
        std::cerr << "Error less then two fighters ids\n";
        return -1;
    }

    int looser_id = ids[0];
    for (const auto id: ids) {
        if (organisms_[looser_id]->GetStr() > organisms_[id]->GetStr()) {
            looser_id = id;
        }
    }

    return looser_id;
}

std::unique_ptr<Organism> WorldManager::CreateBaby(const std::vector<Position> &positions, OrganismTypes parent_race) {
    std::vector<std::unique_ptr<Organism> > new_babies;
    const auto c_pos = GetChildSpawnPosition(positions);
    auto child = SpawnAnimals(parent_race, c_pos);
    if (!child) {
        std::cerr << "Error while spawning child\n";
        return child;
    }

    auto parent_ids = GetOrganismIdsAtPositions(positions);
    std::cout << parent_ids.size() << '\n';
    for (const auto id : parent_ids) {
        std::cout << "Parent at: " << organisms_[id]->GetPosition().x << ' ' << organisms_[id]->GetPosition().y << '\n';
        organisms_[id]->SetChild(true);
    }
    std::cout << "New child at: " << c_pos.x << ' ' << c_pos.y << '\n';

    return child;
}

void WorldManager::Update() {
    std::cout << "Before update:\n";
    Render();
    std::cout << std::endl;

    std::vector<std::unique_ptr<Organism> > new_babies;
    std::vector<int> loosers;

    for (const auto &organism: organisms_) {
        auto [interaction, pos] = organism->Update();
        switch (interaction) {
            case InteractionTypes::FIGHT: {
                loosers.push_back(CreateFight(pos));
                break;
            }
            case InteractionTypes::REPRODUCE: {
                new_babies.push_back(CreateBaby(pos, organism->GetType()));
                break;
            }
            case InteractionTypes::MOVE:
                break;
            default: {
                std::cerr << "Error while performing and update on organism\n";
                break;
            }
        }
    }

    const bool need_sort = !loosers.empty() || !new_babies.empty();

    std::sort(loosers.rbegin(), loosers.rend());
    loosers.erase(std::unique(loosers.begin(), loosers.end()), loosers.end());
    for (const auto loser: loosers) {
        if (loser != -1 ) organisms_.erase(organisms_.begin() + loser);
    }

    for (auto &baby: new_babies) {
        organisms_.push_back(std::move(baby));
    }

    if (need_sort) {
        SortOrganisms();
    }

    std::cout << "After update:\n";
    Render();
}

void WorldManager::Render() {
    // clear whole plane
    for (auto &row: world_map_) {
        for (auto &tile: row) {
            tile = '#';
        }
    }
    // paint the rest with all the orgs draw funcs
    for (const auto &organism: organisms_) {
        organism->Render();
    }
    for (const auto &row: world_map_) {
        std::cout << " | ";
        for (const auto tile: row) {
            std::cout << tile << " | ";
        }
        std::cout << std::endl;
    }
}

std::unique_ptr<Organism> WorldManager::SpawnAnimals(const OrganismTypes type, const Position &spawn_pos) {
    std::unique_ptr<Organism> temp;
    switch (type) {
        // Wolf
        case OrganismTypes::WOLF: {
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
