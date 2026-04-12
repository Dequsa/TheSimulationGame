//
// Created by marci on 3/29/2026.
//

#include "./Turtle.h"

Position Turtle::SetMovementVector(const DIRECTIONS dir) {
    auto direction = dir;
    // 75% chance of staying
    if (rand() % 4 < 3) {
        is_moving_ = false;
        direction = DIRECTIONS::MID_MID;
        return Animal::SetMovementVector(direction);
    }

    if (direction != DIRECTIONS::MID_MID) {
        is_moving_ = true;
    }
    return Animal::SetMovementVector(direction);
}

bool Turtle::SpecialCheck(const Organism &other) const {
    if (!is_moving_) {
        return other.GetStr() <= TURTLE::MAX_DEFLECT_STR;
    }
    return false;
}

void Turtle::SpecialAbility() {
    std::cout<< *this << " is deflecting enemy" << '\n';
    // he does nothing just stands there
}
