//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_WORLDMANAGER_H
#define C__1_WORLDMANAGER_H
#pragma once
#include "Utils.h"
#include <vector>
#include <memory>

class Organism;
struct AnimalData;
struct UpdateData;

namespace ReturnCodes {
    constexpr int OK = 0;
    constexpr int ERROR = -1;
    constexpr int SPECIAL_ABILITY = -2;
    constexpr int SPECIAL_DEFENDER = -3;
}

class WorldManager {
    std::vector<std::unique_ptr<Organism> > organisms_;
    std::vector<std::vector<char> > world_map_;

    // special abilities
    bool CheckIfAttackerIsFox(const Organism &org1, const Organism &org2);

    Position ChooseAndSetSpawnPoint() const;

    Position GetChildSpawnPosition(const std::vector<Position> &positions) const;

    std::vector<int> GetOrganismIdsAtPositions(const std::vector<Position> &positions) const;

    void CreateFight(std::vector<int> &loosers, const std::unique_ptr<Organism> &organism,
                     const std::vector<Position> &pos);

    int GetFightLoosersId(const std::vector<Position> &positions) const;

    void Reproduce(std::vector<std::unique_ptr<Organism> > &new_babies, const std::vector<Position> &pos, const OrganismTypes parent_race);

    std::unique_ptr<Organism> CreateBaby(const std::vector<Position> &positions, OrganismTypes parent_race);

    bool AddOrganisms(std::vector<std::unique_ptr<Organism> > &new_organisms);
    bool DeleteOrganismsByIds(std::vector<int> &delete_ids);

    void ResetActivityAllOrganisms();

    void SortOrganisms();

public:
    WorldManager(const int map_size, const int organism_count);

    ~WorldManager();

    void Update();

    std::unique_ptr<Organism> SpawnAnimals(const OrganismTypes type, const Position &spawn_pos);

    void KillOrganism();

    void Render();

    std::vector<std::vector<char> > &GetWorldMap() { return world_map_; }
};


#endif //C__1_WORLDMANAGER_H
