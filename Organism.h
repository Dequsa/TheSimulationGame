//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ORGANISM_H
#define C__1_ORGANISM_H
#include <memory>
#include <vector>
#include "Utils.h"
#include "WorldManager.h"
#pragma once

class Organism {
private:
    Position pos_{};
    int str_{};
    int init_{};
    std::vector<std::vector<char>> &world_map_;

    Position ChooseAndSetSpawnPoint();

public:

    Organism(std::vector<std::vector<char>> &world_map, const int &str, const int &init);

    Organism(std::vector<std::vector<char>> &world_map, const int &str, const int &init, const Position &pos);

    Organism(const Organism &org) = default;

    virtual ~Organism() = 0;

    virtual void Update() = 0;

    // organism getters
    Position GetPosition() const;

    int GetStr();

    int GetInit();
};

#endif //C__1_ORGANISM_H
