//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ORGANISM_H
#define C__1_ORGANISM_H
#pragma once
#include <memory>
#include <vector>
#include "Utils.h"
class Organism {
protected:
    static uint32_t global_id_counter_;
    std::vector<std::vector<char> > &world_map_;
    Position pos_{};
    uint32_t id_{};
    uint8_t str_{};
    uint8_t init_{};
    uint8_t sprite_{};

public:
    // Organism(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    Organism(std::vector<std::vector<char> > &world_map, const AnimalData &data, const Position &pos) : world_map_(world_map),
                                    pos_(pos),
                                    str_(data.str),
                                    init_(data.init),
                                    sprite_(data.sprite) {
        id_ = global_id_counter_++;
    }

    // Organism(std::vector<std::vector<char> > &world_map, const int str, const int init, const char sprite,
    //      const Position &pos) : world_map_(world_map),
    //                             pos_(pos),
    //                             str_(str),
    //                             init_(init),
    //                             sprite_(sprite) {
    //     id_ = global_id_counter_++;
    // }

    Organism(const Organism &org) = default;

    virtual ~Organism() = default;

    virtual void Update() = 0;

    // organism getters
    Position GetPosition() const;

    int GetStr() const;

    int GetInit() const;
};

#endif //C__1_ORGANISM_H
