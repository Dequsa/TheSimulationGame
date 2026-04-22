#include "WorldManager.h"
#include <ctime>
#include <ncurses.h>
// #include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "./Animals/Wolf.h"
#include "Animals/Antelope.h"
#include "Animals/Fox.h"
#include "Animals/Human.h"
#include "Animals/Sheep.h"
#include "Animals/Turtle.h"
#include "Plants/Belladona.h"
#include "Plants/Grass.h"
#include "Plants/Guarana.h"
#include "Plants/Hogweed.h"
#include "Plants/SowThistle.h"

WorldManager::WorldManager(const int map_size, const int organism_count, const bool load) : world_map_(
    map_size, std::vector<Organism *>(map_size, nullptr)) {
    std::srand(time(NULL));

    if (load) {
        if (!LoadGame(SAVE_FILE_PATH)) return;
        SortOrganisms();
        Render();
    } else {
        for (int i = 0; i < organism_count; i++) {
            Position spawn_pos = ChooseAndSetSpawnPoint();

            if (spawn_pos.x == -1 || spawn_pos.y == -1) {
                i--;
                continue;
            }

            int animal_num = 0;
            if (i == 0) {
                animal_num = static_cast<int>(OrganismTypes::HUMAN);
            } else {
                animal_num = rand() % static_cast<int>(OrganismTypes::NONE);
            }

            organisms_.push_back(SpawnAnimals(static_cast<OrganismTypes>(animal_num), spawn_pos));
        }
        SortOrganisms();

        Render();
    }
}

WorldManager::~WorldManager() {
    organisms_.clear();
    organisms_.shrink_to_fit();

    world_map_.clear();
    world_map_.shrink_to_fit();
}

void WorldManager::SortOrganisms() {
    std::erase_if(organisms_, [](const std::unique_ptr<Organism> &org) {
        return org == nullptr;
    });

    std::sort(organisms_.begin(), organisms_.end(),
              [](const std::unique_ptr<Organism> &a, const std::unique_ptr<Organism> &b) {
                  if (a->GetInit() == b->GetInit()) {
                      return a->GetAge() > b->GetAge();
                  }
                  return a->GetInit() > b->GetInit();
              });
}

bool WorldManager::CheckMapContains(const std::vector<Position> &positions) {
    for (const auto [x, y]: positions) {
        if (x == -1 || y == -1) {
            std::ostringstream oss;
            oss << "Error while creating a baby or a fight at pos: " << x << ' ' << y << '\n';
            message_buffer_.push_back(oss.str());
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
    constexpr int MAX_TRIES = 200;

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

    const auto attacker = world_map_[positions[0].y][positions[0].x];
    const auto defender = world_map_[positions[1].y][positions[1].x];

    if (attacker == defender) {
        return {ReturnCodes::ERROR, nullptr};
    }

    if (attacker->SpecialCheck(*defender)) {
        attacker->SpecialAbility(message_buffer_);
        return {ReturnCodes::SPECIAL_ABILITY, nullptr};
    }

    if (defender->SpecialCheck(*attacker)) {
        defender->SpecialAbility(message_buffer_);
        return {ReturnCodes::SPECIAL_DEFENDER, nullptr};
    }

    // check if it's a plant
    std::ostringstream oss;
    if (defender->GetType() <= OrganismTypes::WOLF) {
        oss << *attacker << " is eating " << *defender << '\n';
    } else if (attacker->GetType() <= OrganismTypes::WOLF) {
        oss << *attacker << " is attacking " << *defender << '\n';
    } else {
        oss << *attacker << " is attacking " << *defender << '\n';
    }


    Organism *lost = nullptr;
    Organism *win = nullptr;

    if (attacker->GetStr() >= defender->GetStr()) {
        win = attacker;
        lost = defender;
    } else {
        win = defender;
        lost = attacker;
    }

    oss << lost->GetType() << " died :(\n";

    lost->FreeSpace();

    if (win == attacker) {
        attacker->FreeSpace();

        win->SetPosition(lost->GetPosition());
    }

    lost->SetLife(false);

    message_buffer_.push_back(oss.str());
    return {ReturnCodes::OKAY, lost};
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

    std::ostringstream oss;
    if (!child) {
        oss << "Error while spawning child: Not enough Space\n";
        message_buffer_.push_back(oss.str());
        return {ReturnCodes::ERROR, nullptr};
    }

    oss << "New child: " << *child << '\n';

    child->Render();

    message_buffer_.push_back(oss.str());
    return {ReturnCodes::OKAY, std::move(child)};
}

BabyResults WorldManager::SowPlant(const OrganismTypes parent_race,
                                   const Position c_pos) {
    auto small_plant = SpawnAnimals(parent_race, c_pos);
    std::ostringstream oss;

    if (!small_plant) {
        oss << "Error while sowing plants\n";
        message_buffer_.push_back(oss.str());
        return {ReturnCodes::ERROR, nullptr};
    }

    oss << "New plant: " << *small_plant << '\n';

    small_plant->Render();

    message_buffer_.push_back(oss.str());
    return {ReturnCodes::OKAY, std::move(small_plant)};
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

    std::ostringstream oss;
    for (const auto parent: parents) {
        if (parents.size() == 1) {
            oss << "Seed flew from: " << *parent << '\n';
        } else {
            oss << "Parent: " << *parent << '\n';
        }

        parent->SetActive(true);
    }

    if (parents.size() == 2) {
        return MakeLife(parent_race, c_pos);
    }

    if (parents.size() == 1) {
        return SowPlant(parent_race, c_pos);
    }

    message_buffer_.push_back(oss.str());
    return {ReturnCodes::ERROR, nullptr};
}

void WorldManager::CreateFight(std::vector<Organism *> &losers, const std::unique_ptr<Organism> &organism,
                               const std::vector<Position> &pos) {
    auto [code, loser] = GetFightLosers(pos);

    if (loser == nullptr) {
        return;
    }

    if (code == ReturnCodes::SPECIAL_ABILITY) {
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

std::vector<Organism *> WorldManager::FindAffected(const std::vector<Position> &positions) const {
    std::vector<Organism *> dead;
    for (const auto &[x, y]: positions) {
        if (world_map_[y][x] == nullptr) continue;
        dead.push_back(world_map_[y][x]);
    }

    return dead;
}

void WorldManager::KillArea(std::vector<Organism *> &losers, const std::vector<Position> &positions) {
    const std::vector<Organism *> dead = FindAffected(positions);

    for (const auto &org: dead) {
        org->SetActive(true);
        org->SetLife(false);

        std::ostringstream oss;
        oss << *org << " got killed by AOE attack.\n";
        message_buffer_.push_back(oss.str());
        losers.push_back(org);
    }
}


bool WorldManager::Update(const char key) {
    if (key == KEYS::SAVE) {
        SaveGame(SAVE_FILE_PATH);
        return false;
    }

    std::ostringstream oss;
    oss << "Current Turn: " << turn_num_++ << '\n';

    ResetActivityAllOrganisms();
    std::vector<std::unique_ptr<Organism> > new_babies;
    std::vector<Organism *> losers;

    for (const auto &organism: organisms_) {
        constexpr int time_period = 1;
        organism->AgeUp(time_period);

        if (organism->GetActivity()) continue;

        organism->SetPlayerInput(key);

        auto [interaction, pos] = organism->Update(message_buffer_);

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
            case InteractionTypes::NONE:
                break;

            case InteractionTypes::AOE_KILL: {
                KillArea(losers, pos);
                break;
            }

            default: {
                oss << "Error while performing and update on organism\n";
                break;
            }
        }
    }

    message_buffer_.push_back(oss.str());

    bool need_sort = false;

    const bool added = AddOrganisms(new_babies);
    const bool deleted = DeleteOrganisms(losers);

    need_sort = added || deleted;

    if (need_sort) {
        SortOrganisms();
    }

    Render();

    return true;
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
    clear();

    bool is_human_alive = false;
    for (const auto &org: organisms_) {
        org->Render();
        if (org->GetType() == OrganismTypes::HUMAN && org->GetLife()) {
            is_human_alive = true;
        }
    }

    for (const auto &row: world_map_) {
        printw(" | ");
        for (const auto tile: row) {
            if (tile) {
                printw("%c | ", tile->GetSprite());
            } else {
                printw("%c | ", MapSprites::EMPTY);
            }
        }
        printw("\n");
    }

    if (is_human_alive) {
        printw("\nUse W/A/S/D to move. Press F to drink magic potion. Press O to save. Press X to exit.\n");
    } else {
        printw("\nPress any to make a turn. Press O to save. Press X to exit.\n");
    }

    for (const auto &msg: message_buffer_) {
        printw("%s", msg.c_str());
    }
    message_buffer_.clear();
    refresh();
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
        case OrganismTypes::HOGWEED: {
            return std::make_unique<Hogweed>(world_map_, spawn_pos);
        }
        case OrganismTypes::HUMAN: {
            return std::make_unique<Human>(world_map_, spawn_pos);
        }
        default: {
            std::ostringstream oss;
            oss << "Unknown AnimalType" << std::endl;
            message_buffer_.push_back(oss.str());
        }
    }
    return nullptr;
}

bool WorldManager::LoadGame(const std::string &filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Could not open file " << filename << std::endl;
        return false;
    }
    std::string line;

    // skip the map size line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int type = -1;
        int x = -1;
        int y = -1;
        int str = -1;
        int init = -1;

        iss >> type >> y >> x >> str >> init;

        if (type < 0 || y < 0 || x < 0 || init < 0) {
            return false;
        }

        auto org = SpawnAnimals(static_cast<OrganismTypes>(type), {x, y});

        if (org) {
            org->SetStr(str);
            org->SetInit(init);
            organisms_.push_back(std::move(org));
        } else {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

bool WorldManager::SaveGame(const std::string &filename) {
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Could not open file " << filename << std::endl;
        return false;
    }

;

    file << static_cast<int>(world_map_.size()) << ' ' << static_cast<int>(organisms_.size()) << '\n';

    for (const auto &org: organisms_) {
        org->Save(file);
    }
    file.close();
    return true;
}
