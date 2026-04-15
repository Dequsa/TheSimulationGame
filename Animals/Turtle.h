//
// Created by marci on 3/29/2026.
//

#ifndef C__1_TURTLE_H
#define C__1_TURTLE_H
#include "../Animals.h"

namespace TURTLE {
    constexpr int STR = 2;
    constexpr int INIT = 1;
    constexpr char SPRITE = 'T';
    constexpr int MAX_DEFLECT_STR = 5;
}

class Turtle final : public Animal {
    static constexpr AnimalData wolf_data_ = {
        TURTLE::STR,
        TURTLE::INIT,
        TURTLE::SPRITE,
        OrganismTypes::TURTLE
    };

    bool is_moving_{};

public:
    Turtle(std::vector<std::vector<Organism*> > &world_map, const Position &spawn_pos) : Animal(
        world_map, wolf_data_, spawn_pos) {
    }

    ~Turtle() override = default;

    Position SetMovementVector(const DIRECTIONS dir) override;

    bool SpecialCheck(const Organism &other) const override;

    void SpecialAbility() override;
};



#endif //C__1_TURTLE_H