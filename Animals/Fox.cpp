//
// Created by marci on 3/29/2026.
//

#include "./Fox.h"

bool Fox::SpecialCheck(const Organism &other) const {
    if (!is_moving_) {
        return false;
    }
    return str_ < other.GetStr();
}

void Fox::SpecialAbility() {
    MoveToPosition(last_pos_);
}

Position Fox::SetMovementVector(const DIRECTIONS dir) {
    if (dir != DIRECTIONS::MID_MID) {
        is_moving_ = true;
    }
    return Animal::SetMovementVector(dir);
}

InteractionTypes Fox::CheckCollision() {
    last_pos_ = pos_;
    return Animal::CheckCollision();
}
