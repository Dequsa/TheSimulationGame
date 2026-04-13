//
// Created by marci on 3/29/2026.
//

#ifndef C__1_ANTELOPE_H
#define C__1_ANTELOPE_H
#include "../Animals.h"

namespace ANTELOPE {
    constexpr int STR = 4;
    constexpr int INIT = 4;
    constexpr char SPRITE = 'A';
    constexpr int JUMP_DISTANCE = 2;
}

class Antelope final : public Animal {
    static constexpr AnimalData wolf_data_ = {
        ANTELOPE::STR,
        ANTELOPE::INIT,
        ANTELOPE::SPRITE,
        OrganismTypes::ANTELOPE
    };

    bool is_moving_{};

public:
    Antelope(std::vector<std::vector<char> > &world_map, const Position &spawn_pos) : Animal(
        world_map, wolf_data_, spawn_pos) {
    }

    ~Antelope() override = default;

    Position SetMovementVector(const DIRECTIONS dir) override;

    bool SpecialCheck(const Organism &other) const override;

    void SpecialAbility() override;
};


#endif //C__1_ANTELOPE_H