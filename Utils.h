//
// Created by marci on 3/29/2026.
//

#ifndef C__1_UTILS_H
#define C__1_UTILS_H

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

namespace MapSprites {
    constexpr char EMPTY = '#';
}

#endif //C__1_UTILS_H
