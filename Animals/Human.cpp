//
// Created by marci on 4/15/2026.
//

#include "Human.h"

DIRECTIONS Human::ChooseDir(const char key) {
    switch (key) {
        case 'w':
            return DIRECTIONS::UP_MID;
        case 's':
            return DIRECTIONS::BOT_MID;
        case 'a':
            return DIRECTIONS::MID_LEFT;
        case 'd':
            return DIRECTIONS::MID_RIGHT;
        default:
            std::cerr << "Invalid key: " << key << '\n';
            return DIRECTIONS::MID_MID;
    }
}

// UpdateData Human::Update(const char key) {
//     UpdateData data;
//
//     ChooseDir(key);
// }
