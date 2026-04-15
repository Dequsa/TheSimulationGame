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
#include "Plants/Belladona.h"
#include "Plants/Grass.h"
#include "Plants/Guarana.h"
#include "Plants/SowThistle.h"

constexpr int MAX_TRIES = 200;

WorldManager::WorldManager(const int map_size, const int organism_count) : world_map_(
    map_size, std::vector<Organism *>(map_size, nullptr)) {
    std::srand(time(NULL));
    // add organisms to the world_map
    for (int i = 0; i < organism_count; i++) {
        Position spawn_pos = ChooseAndSetSpawnPoint();

        if (spawn_pos.x == -1 || spawn_pos.y == -1) {
            i--;
            continue;
        }

        const int animal_num = rand() % static_cast<int>(OrganismTypes::NONE);

        organisms_.push_back(SpawnAnimals(static_cast<OrganismTypes>(animal_num), spawn_pos));
    }
    SortOrganisms();

    Render();
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


// std::vector<int> WorldManager::GetOrganismIdsAtPositions(const std::vector<Position> &positions) const {
//     std::vector<int> ids;
//
//     for (const auto target_pos: positions) {
//         for (int i = 0; i < organisms_.size(); i++) {
//             if (organisms_[i]->GetPosition() == target_pos && organisms_[i]->GetLife()) {
//                 // check for duplicates
//                 if (std::find(ids.begin(), ids.end(), i) == ids.end()) {
//                     ids.push_back(i);
//                     break;
//                 }
//             }
//         }
//     }
//     return ids;
// }

bool WorldManager::CheckMapContains(const std::vector<Position> &positions) const {
    for (const auto [x, y]: positions) {
        if (x == -1 || y == -1) {
            std::cerr << "Error while creating a baby or a fight at pos: " << x << ' ' << y << '\n';
            return false;
        }
    }

    for (const auto [x, y]: positions) {
        if (x < 0 || y < 0 || y >= world_map_.size() || x >= world_map_[0].size()) {
            return false;
        }

        if (world_map_[y][x] != nullptr) {
            world_map_[y][x]->SetActive(true);
        } else {
            return false;
        }
    }

    return true;
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
        if (world_map_[r_y][r_x] == nullptr) {
            return Position{r_x, r_y};
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (world_map_[r_y + i][r_x + j] == nullptr) {
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
                if (world_map_[c_pos.y][c_pos.x] == nullptr) {
                    return c_pos;
                }
            }
        }
    }
    return {-1, -1};
}

// position 0 is position of the one who starts the fight
FightResults WorldManager::GetFightLosers(const std::vector<Position> &positions) {
    if (!CheckMapContains(positions)) {
        return {ReturnCodes::ERROR, nullptr};
    }

    if (positions.size() < 2) return {ReturnCodes::ERROR, nullptr};

    auto attacker = world_map_[positions[0].y][positions[0].x];
    auto defender = world_map_[positions[1].y][positions[1].x];

    if (attacker == defender) {
        return {ReturnCodes::ERROR, nullptr};
    }

    if (attacker->SpecialCheck(*defender)) {
        return {ReturnCodes::SPECIAL_ABILITY, nullptr};
    }

    if (defender->SpecialCheck(*attacker)) {
        defender->SpecialAbility();
        return {ReturnCodes::SPECIAL_DEFENDER, nullptr};
    }

    std::cout << *attacker << " is attacking " << *defender << '\n';

    Organism *lost = nullptr;
    Organism *win = nullptr;

    if (attacker->GetStr() >= defender->GetStr()) {
        win = attacker;
        lost = defender;
    } else {
        win = defender;
        lost = attacker;
    }

    std::cout << lost->GetType() << " died :(\n";

    lost->FreeSpace();

    if (win == attacker) {
        attacker->FreeSpace();

        win->SetPosition(lost->GetPosition());
    }

    lost->SetLife(false);

    return {ReturnCodes::OK, lost};
}

void WorldManager::Reproduce(std::vector<std::unique_ptr<Organism> > &new_babies, const std::vector<Position> &pos,
                             const OrganismTypes parent_race) {
    auto results = CreateBaby(pos, parent_race);

    if (results.code == ReturnCodes::ERROR) {
        return;
    }

    if (results.baby) {
        new_babies.push_back(std::move(results.baby));
    }
}

BabyResults WorldManager::MakeLife(const OrganismTypes parent_race, const Position c_pos) {

    auto child = SpawnAnimals(parent_race, c_pos);

    if (!child) {
        std::cerr << "Error while spawning child\n";
        return {ReturnCodes::ERROR, nullptr};
    }

    std::cout << "New child: " << *child << '\n';

    child->Render();

    return {ReturnCodes::OK, std::move(child)};
}

BabyResults WorldManager::SowPlant(const OrganismTypes parent_race,
                                   const Position c_pos) {
    auto small_plant = SpawnAnimals(parent_race, c_pos);

    if (!small_plant) {
        std::cerr << "Error while sowing plants\n";
        return {ReturnCodes::ERROR, nullptr};
    }

    std::cout << "New plant: " << *small_plant << '\n';

    small_plant->Render();

    return {ReturnCodes::OK, std::move(small_plant)};
}

BabyResults WorldManager::CreateBaby(const std::vector<Position> &positions, const OrganismTypes parent_race) {
    const auto c_pos = GetChildSpawnPosition(positions);

    if (!CheckMapContains(positions)) {
        return {ReturnCodes::ERROR, nullptr};
    }

    std::vector<Organism *> parents;

    for (const auto [x, y]: positions) {
        if (world_map_[y][x] != nullptr) {
            parents.push_back(world_map_[y][x]);
        }
    }

    for (const auto parent: parents) {
        if (parents.size() == 1) {
            std::cout << "Seed flew from: " << *parent << '\n';
        } else {
            std::cout << "Parent: " << *parent << '\n';
        }

        parent->SetActive(true);
    }

    if (parents.size() == 2) {
        return MakeLife(parent_race, c_pos);
    }

    if (parents.size() == 1) {
        return SowPlant(parent_race, c_pos);
    }

    return {ReturnCodes::ERROR, nullptr};
}

void WorldManager::CreateFight(std::vector<Organism *> &losers, const std::unique_ptr<Organism> &organism,
                               const std::vector<Position> &pos) {
    auto [code, loser] = GetFightLosers(pos);

    if (loser == nullptr) {
        return;
    }

    if (code == ReturnCodes::SPECIAL_ABILITY) {
        organism->SpecialAbility();
        return;
    }

    // no fight defender used special escape / deflect ability
    if (code == ReturnCodes::SPECIAL_DEFENDER) {
        return;
    }

    losers.push_back(loser);
}

void WorldManager::ResetActivityAllOrganisms() {
    for (const auto &org: organisms_) {
        org->SetActive(false);
    }
}

void WorldManager::Update() {
    ResetActivityAllOrganisms();
    std::vector<std::unique_ptr<Organism> > new_babies;
    std::vector<Organism *> losers;

    for (const auto &organism: organisms_) {
        constexpr int time_period = 1;
        organism->AgeUp(time_period);

        if (organism->GetActivity()) continue;

        auto [interaction, pos] = organism->Update();

        organism->SetActive(true);

        switch (interaction) {
            case InteractionTypes::FIGHT: {
                CreateFight(losers, organism, pos);
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
    const bool deleted = DeleteOrganisms(losers);

    need_sort = added || deleted;

    if (need_sort) {
        SortOrganisms();
    }

    Render();
}

bool WorldManager::AddOrganisms(std::vector<std::unique_ptr<Organism> > &new_organisms) {
    if (new_organisms.empty()) {
        return false;
    }
    for (auto &org: new_organisms) {
        if (org == nullptr) continue;

        organisms_.push_back(std::move(org));
    }

    return true;
}


bool CheckDelete(const int id) {
    if (id == ReturnCodes::ERROR || id == ReturnCodes::SPECIAL_ABILITY || id == ReturnCodes::SPECIAL_DEFENDER) {
        return false;
    }
    return true;
}

bool WorldManager::DeleteOrganisms(std::vector<Organism *> &dead) {
    if (dead.empty()) {
        return false;
    }

    for (auto &dead_org: dead) {
        if (dead_org != nullptr) {
            std::erase_if(organisms_, [dead_org](const std::unique_ptr<Organism> &org) {
                return org.get() == dead_org;
            });
        }
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
            if (tile) {
                std::cout << tile->GetSprite() << " | ";
            } else {
                std::cout << MapSprites::EMPTY << " | ";
            }
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
        case OrganismTypes::ANTELOPE: {
            return std::make_unique<Antelope>(world_map_, spawn_pos);
        }
        case OrganismTypes::GRASS: {
            return std::make_unique<Grass>(world_map_, spawn_pos);
        }
        case OrganismTypes::SOWTHISTLE: {
            return std::make_unique<SowThistle>(world_map_, spawn_pos);
        }
        case OrganismTypes::GUARANA: {
            return std::make_unique<Guarana>(world_map_, spawn_pos);
        }
        case OrganismTypes::BELLADONNA: {
            return std::make_unique<Belladonna>(world_map_, spawn_pos);
        }
        default: {
            std::cerr << "Unknown AnimalType" << std::endl;
        }
    }
    return nullptr;
}
