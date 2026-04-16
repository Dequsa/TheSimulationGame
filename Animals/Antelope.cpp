#include "./Antelope.h"

#include <ncurses.h>
#include <sstream>

Position Antelope::SetMovementVector(const DIRECTIONS dir) {
    auto jump_move = Animal::SetMovementVector(dir);

    jump_move *= ANTELOPE::JUMP_DISTANCE;

    return jump_move;
}

bool Antelope::SpecialCheck(const Organism &other) const {
    // 50 | 50 it may or may not evade the fight
    return rand() & 1;
}

void Antelope::SpecialAbility( std::vector<std::string> &message_buffer) {
    std::ostringstream oss;
    oss << *this << " has avoided the fight :)\n";
    message_buffer.push_back(oss.str());
}
