#include "./Antelope.h"

Position Antelope::SetMovementVector(const DIRECTIONS dir) {
    auto jump_move = Animal::SetMovementVector(dir);

    jump_move *= ANTELOPE::JUMP_DISTANCE;

    return jump_move;
}

bool Antelope::SpecialCheck(const Organism &other) const {
    // 50 | 50 it may or may not evade the fight
    return rand() & 1;
}

void Antelope::SpecialAbility() {
    std::cout << *this << " has avoided the fight :)\n";
}
