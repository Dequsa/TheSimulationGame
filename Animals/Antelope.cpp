#include "./Antelope.h"

Position Antelope::SetMovementVector(const DIRECTIONS dir) {
    auto [vx, vy] = Animal::SetMovementVector(dir);
    vx *= ANTELOPE::JUMP_DISTANCE;
    vy *= ANTELOPE::JUMP_DISTANCE;
    return {vx, vy};
}

bool Antelope::SpecialCheck(const Organism &other) const {
    return rand() & 1;
}

void Antelope::SpecialAbility() {
    std::cout << *this << " has avoided the fight :)\n";
}
