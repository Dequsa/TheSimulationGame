//
// Created by marci on 3/29/2026.
//

#ifndef C__1_UTILS_H
#define C__1_UTILS_H
#pragma once
#include <iostream>


class Organism;
class Plants;

struct Position {
    Position &operator+=(const Position &that) {
        this->x += that.x;
        this->y += that.y;
        return *this;
    }

    Position &operator*=(const int n) {
        this->x *= n;
        this->y *= n;
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

    DIR_COUNT,

    HUMAN_SPECIAL
};

enum class OrganismTypes {
    GRASS,
    SOWTHISTLE,
    GUARANA,
    BELLADONNA,
    HOGWEED,
    // below 5 plants

    // above and equal 5 animals
    WOLF, // 5
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    NONE, // can be also used as count of types
    HUMAN,
};

std::ostream &operator<<(std::ostream &os, const OrganismTypes type);

std::ostream &operator<<(std::ostream &os, const Position &pos);

std::ostream &operator<<(std::ostream &os, const Organism &org);

std::ostream &operator<<(std::ostream &os, const Plants &org);

enum class InteractionTypes {
    FIGHT,
    REPRODUCE,
    MOVE,
    AOE_KILL,
    NONE
};

struct AnimalData {
    const int str;
    const int init;
    const char sprite;
    const OrganismTypes type;
};

struct PlantData {
    const int str;
    const char sprite;
    const OrganismTypes type;
};

namespace MapSprites {
    constexpr char EMPTY = '.';
}

namespace KEYS {
    constexpr char SAVE = 'o';
    constexpr char UP = 'w';
    constexpr char DOWN = 's';
    constexpr char LEFT = 'a';
    constexpr char RIGHT = 'd';
    constexpr char EXIT = 'x';
    constexpr char ABILITY = 'f';
}

#endif //C__1_UTILS_H
