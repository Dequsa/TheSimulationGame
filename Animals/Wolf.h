//
// Created by marci on 3/29/2026.
//

#ifndef C__1_WOLF_H
#define C__1_WOLF_H
#include "../Animals.h"

class Wolf final : public Animal {
    int strength_ = 9;
    int initiative_ = 5;
    Position pos_{};
public:
    Wolf();

    ~Wolf() override;
};


#endif //C__1_WOLF_H
