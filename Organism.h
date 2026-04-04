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
protected:
    static uint32_t global_id_counter_;
    std::vector<std::vector<char> > &world_map_;
    Position pos_{};
    uint32_t id_{};
    uint8_t str_{};
    uint8_t init_{};

    Position ChooseAndSetSpawnPoint();

public:
    // Organism(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    Organism(std::vector<std::vector<char> > &world_map, const int str, const int init, const Position &pos) :
                                    world_map_(world_map),
                                    pos_(pos),
                                    str_(str),
                                    init_(init)
    {
                                    id_ = global_id_counter_++;
    }

    Organism(const Organism &org) = default;

    virtual ~Organism() = 0;

    virtual void Update() = 0;

    // organism getters
    Position GetPosition() const;

    int GetStr() const;

    int GetInit() const;
};

#endif //C__1_ORGANISM_H
