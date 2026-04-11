//
// Created by marci on 3/29/2026.
//

#ifndef C__1_FOX_H
#define C__1_FOX_H
#include "../Animals.h"

namespace FOX{
    constexpr int STR = 3;
    constexpr int INIT = 7;
    constexpr char SPRITE = 'F';
}

class Fox final : public Animal {
    static constexpr AnimalData Fox_data_ = {
        FOX::STR,
        FOX::INIT,
        FOX::SPRITE,
        OrganismTypes::FOX
    };
    bool is_moving_{};
    Position last_pos_{};

public:
    Fox(std::vector<std::vector<char> > &world_map, const Position &spawn_pos) : Animal(
        world_map, Fox_data_, spawn_pos) {
    }

    ~Fox() override = default;

    bool SpecialCheck(const Organism &other) const override;

    void SpecialAbility() override;

    Position SetMovementVector(const DIRECTIONS dir) override;

    InteractionTypes CheckCollision() override;
};


#endif //C__1_FOX_H