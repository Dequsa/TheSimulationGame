//
// Created by marci on 3/29/2026.
//

#ifndef C__1_UTILS_H
#define C__1_UTILS_H
#pragma once
#include <iostream>
#include "Animals.h"

struct Position {
    Position &operator+=(const Position &that) {
        this->x += that.x;
        this->y += that.y;
        return *this;
    }

    Position operator+(const Position &that) const {
        Position res{};
        res.x = this->x + that.x;
        res.y = this->y + that.y;
        return res;
    }

    bool operator==(const Position &that) const {
        return this->x == that.x && this->y == that.y;
    }

    int x;
    int y;
};

enum class DIRECTIONS {
    UP_LEFT,
    UP_MID,
    UP_RIGHT,
    MID_LEFT,
    MID_MID,
    MID_RIGHT,
    BOT_LEFT,
    BOT_MID,
    BOT_RIGHT,

    DIR_COUNT
};

enum class OrganismTypes {
    WOLF, // 0
    SHEEP, // 1
    FOX, // 2
    TURTLE, // 3
    ANTELOPE, // 4

    NONE // can be also used as count of types
};

std::ostream &operator<<(std::ostream &os, const OrganismTypes type);
std::ostream &operator<<(std::ostream &os, const Position &pos);
std::ostream &operator<<(std::ostream &os, const Organism &org);

enum class InteractionTypes {
    FIGHT,
    REPRODUCE,
    MOVE,
    NONE
};

struct AnimalData {
    const int str;
    const int init;
    const char sprite;
    const OrganismTypes type;
};

namespace MapSprites {
    constexpr char EMPTY = '.';
}

#endif //C__1_UTILS_H
