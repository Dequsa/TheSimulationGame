//
// Created by marci on 3/29/2026.
//

#ifndef C__1_WOLF_H
#define C__1_WOLF_H
#include "../Animals.h"

class Wolf final : public Animal {
public:
    Wolf(std::vector<std::vector<char>> & world_map, const int str, const int init): Animal(world_map, str, init) {};

    ~Wolf() override = default;
};

namespace WOLF {
    constexpr int STR = 9;
    constexpr int INIT = 5;
}


#endif //C__1_WOLF_H
