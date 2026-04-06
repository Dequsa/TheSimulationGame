//
// Created by marci on 3/29/2026.
//

#ifndef C__1_WOLF_H
#define C__1_WOLF_H
#include "../Animals.h"


namespace WOLF {
    constexpr int STR = 9;
    constexpr int INIT = 5;
    constexpr char SPRITE = 'W';
}

class Wolf final : public Animal {
    AnimalData wolf_data_ = {
        WOLF::STR,
        WOLF::INIT,
        WOLF::SPRITE
    };

public:
    Wolf(std::vector<std::vector<char> > &world_map, const Position &spawn_pos) : Animal(
        world_map, wolf_data_, spawn_pos) {
    };

    ~Wolf() override = default;
};


#endif //C__1_WOLF_H
