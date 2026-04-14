//
// Created by Kacper Marciniak on 4/14/26.
//

#include "SowThistle.h"

InteractionTypes SowThistle::CheckCollision() {
    for (int i = 0; i < SOWTHISTLE::MAX_TRIES; i++) {
        const auto collision = Plants::CheckCollision();

        const auto dir = GetMoveDirection();
        move_ = SetMovementVector(dir);

        if (collision != InteractionTypes::NONE) {
            return collision;
        }
    }
    return InteractionTypes::NONE;
}
