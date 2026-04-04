//
// Created by marci on 3/29/2026.
//

#ifndef C__1_UTILS_H
#define C__1_UTILS_H

struct Position {
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

#endif //C__1_UTILS_H