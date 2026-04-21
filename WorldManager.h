//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_WORLDMANAGER_H
#define C__1_WORLDMANAGER_H
#pragma once
#include "Utils.h"
#include <vector>
#include <memory>

constexpr  std::string SAVE_FILE_PATH = "SaveData.txt";

class Organism;
struct AnimalData;
struct UpdateData;
namespace ReturnCodes {
    constexpr int OKAY = 0;
    constexpr int ERROR = -1;
    constexpr int SPECIAL_ABILITY = -2;
    constexpr int SPECIAL_DEFENDER = -3;
}

struct FightResults {
    int code{};
    Organism* loser = nullptr;
};

struct BabyResults {
    int code{};
    std::unique_ptr<Organism> baby;
};

class WorldManager {
    int turn_num_ = 0;
    std::vector<std::unique_ptr<Organism> > organisms_;
    std::vector<std::vector<Organism*> > world_map_;
    std::vector<std::string> message_buffer_;

    // special abilities
    bool CheckIfAttackerIsFox(const Organism &org1, const Organism &org2);

    bool CheckMapContains(const std::vector<Position> &positions);

    Position ChooseAndSetSpawnPoint() const;

    Position GetChildSpawnPosition(const std::vector<Position> &positions) const;

    std::vector<int> GetOrganismIdsAtPositions(const std::vector<Position> &positions) const;

    void CreateFight(std::vector<Organism*> &losers, const std::unique_ptr<Organism> &organism, const std::vector<Position> &pos);

    FightResults GetFightLosers(const std::vector<Position> &positions);

    void Reproduce(std::vector<std::unique_ptr<Organism> > &new_babies, const std::vector<Position> &pos, const OrganismTypes parent_race);

    BabyResults MakeLife(const OrganismTypes parent_race, const Position c_pos);

    BabyResults SowPlant(const OrganismTypes parent_race, const Position c_pos);

    BabyResults CreateBaby(const std::vector<Position> &positions, OrganismTypes parent_race);

    bool AddOrganisms(std::vector<std::unique_ptr<Organism> > &new_organisms);
    bool DeleteOrganisms(std::vector<Organism*> &dead);

    void ResetActivityAllOrganisms();

    std::vector<Organism *> FindAffected(const std::vector<Position> &positions) const;

    void SortOrganisms();

    void KillArea(std::vector<Organism*> &losers, const std::vector<Position> &positions);

    std::unique_ptr<Organism> SpawnAnimals(const OrganismTypes type, const Position &spawn_pos);


public:
    WorldManager() = default;

    WorldManager(const int map_size, const int organism_count, const bool load);

    WorldManager(WorldManager &world_manager) = default;


    ~WorldManager();

    bool Update(const char key);

    void Render();

    bool LoadGame(const std::string &filename);
    bool SaveGame(const std::string &filename);

    std::vector<std::vector<Organism*> > &GetWorldMap() { return world_map_; }
};


#endif //C__1_WORLDMANAGER_H
