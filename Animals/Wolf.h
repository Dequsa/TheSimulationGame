//
// Created by marci on 3/29/2026.
//

#ifndef C__1_WOLF_H
#define C__1_WOLF_H
#include "../Animals.h"


namespace WOLF {
    constexpr int STR = 9;
    constexpr int INIT = 5;
}

class Wolf final : public Animal {
public:
    Wolf(std::vector<std::vector<char> > &world_map, const Position &spawn_pos) : Animal(
        world_map, WOLF::STR, WOLF::INIT, spawn_pos) {
    };

    ~Wolf() override = default;
};


#endif //C__1_WOLF_H
