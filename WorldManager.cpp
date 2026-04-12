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
    map_size, std::vector<char>(map_size, MapSprites::EMPTY)) {
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

        // auto animal_num = static_cast<int>(OrganismTypes::SHEEP);
        auto animal_num = rand() % static_cast<int>(OrganismTypes::ANTELOPE);
        organisms_.push_back(SpawnAnimals(static_cast<OrganismTypes>(animal_num), spawn_pos));
    }
    SortOrganisms();
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
                  if (a->GetInit() == b->GetInit()) {
                      return a->GetAge() > b->GetAge();
                  }
                  return a->GetInit() > b->GetInit();
              });
}


std::vector<int> WorldManager::GetOrganismIdsAtPositions(const std::vector<Position> &positions) const {
    std::vector<int> ids;

    for (const auto target_pos: positions) {
        for (int i = 0; i < organisms_.size(); i++) {
            if (organisms_[i]->GetPosition() == target_pos && organisms_[i]->GetLife()) {
                // check for duplicates
                if (std::find(ids.begin(), ids.end(), i) == ids.end()) {
                    ids.push_back(i);
                    break;
                }
            }
        }
    }
    return ids;
}

Position WorldManager::ChooseAndSetSpawnPoint() const {
    const int max_x = static_cast<int>(world_map_[0].size());
    const int max_y = static_cast<int>(world_map_.size());
    int max_tries = MAX_TRIES;
    // (1 --- max_x - 1) <- range of rand so we can do the search with checking neighbors

    while (max_tries--) {
        const int r_x = rand() % max_x;
        const int r_y = rand() % max_y;

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
                if (c_pos.x < 0 || c_pos.y < 0 || c_pos.y >= world_map_.size() || c_pos.x >= world_map_[0].size()) {
                    continue;
                }
                if (world_map_[c_pos.y][c_pos.x] == MapSprites::EMPTY) {
                    return c_pos;
                }
            }
        }
    }
    return {-1, -1};
}

// position 0 is position of the one who starts the fight
int WorldManager::GetFightLoosersId(const std::vector<Position> &positions) const {
    for (const auto [x, y]: positions) {
        if (x == -1 || y == -1) {
            std::cerr << "Error while creating a fight at pos: " << x << ' ' << y << '\n';
            return -1;
        }
    }

    // 0 - ATTACKER | 1 - DEFENDER
    const std::vector<int> ids = GetOrganismIdsAtPositions(positions);

    if (ids.size() < 2 && !ids.empty()) {
        std::cerr << "Error less then two fighters ids\n";
        std::cout << organisms_[ids[0]] << '\n';
        return ReturnCodes::ERROR;
    }

    for (const auto id :ids ) {
        organisms_[id]->SetActive(true);
    }

    const int attacker_id = ids[0];
    const int defender_id = ids[1];

    if (organisms_[attacker_id]->GetType() == organisms_[defender_id]->GetType()) {
        return ReturnCodes::ERROR;
    }

    if (organisms_[attacker_id]->SpecialCheck(*organisms_[defender_id])) {
        return ReturnCodes::SPECIAL_ABILITY;
    }

    if (organisms_[defender_id]->SpecialCheck(*organisms_[attacker_id])) {
        organisms_[defender_id]->SpecialAbility();
        return ReturnCodes::SPECIAL_DEFENDER;
    }

    std::cout << *organisms_[attacker_id] << " is attacking " << *organisms_[defender_id] << '\n';

    int winner_id, looser_id;

    if (organisms_[attacker_id]->GetStr() >= organisms_[defender_id]->GetStr()) {
        winner_id = attacker_id;
        looser_id = defender_id;
    } else {
        winner_id = defender_id;
        looser_id = attacker_id;
    }

    std::cout << organisms_[looser_id]->GetType() << " died :(\n";

    if (winner_id == attacker_id) {
        organisms_[winner_id]->SetPosition(organisms_[looser_id]->GetPosition());
    }

    organisms_[looser_id]->SetLife(false);

    return looser_id;
}

void WorldManager::Reproduce(std::vector<std::unique_ptr<Organism> > &new_babies, const std::vector<Position> &pos,
                             const OrganismTypes parent_race) {
    auto baby = CreateBaby(pos, parent_race);
    if (baby) {
        new_babies.push_back(std::move(baby));
    }
}

std::unique_ptr<Organism> WorldManager::CreateBaby(const std::vector<Position> &positions,
                                                   const OrganismTypes parent_race) {
    const auto c_pos = GetChildSpawnPosition(positions);

    const auto parent_ids = GetOrganismIdsAtPositions(positions);

    if (parent_ids.size() < 2) return nullptr;

    for (const auto id: parent_ids) {
        std::cout << "Parent: " << *organisms_[id] << '\n';
        organisms_[id]->SetChild(true);
        organisms_[id]->SetActive(true);
    }

    if (c_pos.x == -1 || c_pos.y == -1) {
        std::cout << "Unfortunate miscarriage of:" << parent_race << " :(\n";
        return nullptr;
    }

    auto child = SpawnAnimals(parent_race, c_pos);

    if (!child) {
        std::cerr << "Error while spawning child\n";
        return child;
    }
    std::cout << "New child: " << *child << '\n';

    return child;
}

void WorldManager::CreateFight(std::vector<int> &loosers, const std::unique_ptr<Organism> &organism,
                               const std::vector<Position> &pos) {
    bool success = true;
    const auto looser_id = GetFightLoosersId(pos);

    if (looser_id == ReturnCodes::ERROR) {
        success = false;
    }

    if (looser_id == ReturnCodes::SPECIAL_ABILITY) {
        organism->SpecialAbility();
        success = false;
    }

    // no fight defender used special escape / deflect ability
    if (looser_id == ReturnCodes::SPECIAL_DEFENDER) {
        success = false;
    }

    if (success) {
        loosers.push_back(looser_id);
    }
}

void WorldManager::ResetActivityAllOrganisms() {
    for (const auto &org: organisms_) {
        org->SetActive(false);
    }
}

void WorldManager::Update() {
    ResetActivityAllOrganisms();
    std::vector<std::unique_ptr<Organism> > new_babies;
    std::vector<int> loosers;

    for (const auto &organism: organisms_) {
        constexpr int time_period = 1;
        organism->AgeUp(time_period);

        if (organism->GetActivity()) continue;

        auto [interaction, pos] = organism->Update();

        organism->SetActive(true);

        switch (interaction) {
            case InteractionTypes::FIGHT: {
                CreateFight(loosers, organism, pos);
                break;
            }
            case InteractionTypes::REPRODUCE: {
                Reproduce(new_babies, pos, organism->GetType());
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

    bool need_sort = false;

    const bool added = AddOrganisms(new_babies);
    const bool deleted = DeleteOrganismsByIds(loosers);

    need_sort = added || deleted;

    if (need_sort) {
        SortOrganisms();
    }

    std::cout << "After update:\n";
    Render();
}

bool WorldManager::AddOrganisms(std::vector<std::unique_ptr<Organism> > &new_organisms) {
    if (new_organisms.empty()) {
        return false;
    }
    for (auto &org: new_organisms) {
        organisms_.push_back(std::move(org));
    }

    return true;
}

bool WorldManager::DeleteOrganismsByIds(std::vector<int> &delete_ids) {
    if (delete_ids.empty()) {
        return false;
    }

    std::sort(delete_ids.rbegin(), delete_ids.rend());
    for (const auto loser: delete_ids) {
        if (loser != -1) organisms_.erase(organisms_.begin() + loser);
    }

    return true;
}


void WorldManager::Render() {
    for (const auto &org: organisms_) {
        org->Render();
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
    if (spawn_pos.x == -1 || spawn_pos.y == -1) return nullptr;
    std::unique_ptr<Organism> temp;
    switch (type) {
        // Wolf
        case OrganismTypes::WOLF: {
            return std::make_unique<Wolf>(world_map_, spawn_pos);
        }
        case OrganismTypes::SHEEP: {
            return std::make_unique<Sheep>(world_map_, spawn_pos);
        }
        case OrganismTypes::FOX: {
            return std::make_unique<Fox>(world_map_, spawn_pos);
        }
        case OrganismTypes::TURTLE: {
            return std::make_unique<Turtle>(world_map_, spawn_pos);
        }
        // case AnimalTypes::ANTELOPE: {
        //     return new Antelope();
        // }
        default: {
            std::cerr << "Unknown AnimalType" << std::endl;
        }
    }
    return nullptr;
}
