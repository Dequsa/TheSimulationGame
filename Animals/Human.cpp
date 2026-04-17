#include "Human.h"
#include <sstream>
DIRECTIONS Human::HandleInput(const char key) {
    switch (key) {
        case 'f':
            return DIRECTIONS::HUMAN_SPECIAL;
        case 'w':
            return DIRECTIONS::UP_MID;
        case 's':
            return DIRECTIONS::BOT_MID;
        case 'a':
            return DIRECTIONS::MID_LEFT;
        case 'd':
            return DIRECTIONS::MID_RIGHT;

        default:
            std::cerr << "Invalid key: " << key << '\n';
            return DIRECTIONS::MID_MID;
    }
}

void Human::SetPlayerInput(const char key) {
    current_key_ = key;
}

void Human::BuffDecay() {
    if (buff_time_ > 0) {
        str_--;
        buff_time_--;
        if (buff_time_ == 0) {
            has_buffed_ = true;
        }
    }
}

bool Human::BuffCheck(const DIRECTIONS dir) {
    return dir == DIRECTIONS::HUMAN_SPECIAL;
}

void Human::SpecialAbility(std::vector<std::string> &message_buffer) {
    // potion drink
    if (has_buffed_) {
        return;
    }
    buff_time_ = HUMAN::POTION_STR;
    has_buffed_ = true;

    AddStr(HUMAN::POTION_STR);
    std::ostringstream oss;
    oss << *this << " has drunk a MAGIC POTION.\n";
    message_buffer.push_back(oss.str());
}

UpdateData Human::PrepareFightData() {
    const auto enemy_pos = pos_ + move_;
    UpdateData data = {InteractionTypes::FIGHT, {pos_, enemy_pos}};
    return data;
}

UpdateData Human::Update(std::vector<std::string> &message_buffer) {
    const auto dir = HandleInput(current_key_);

    BuffDecay();

    if (BuffCheck(dir)) {
        SpecialAbility(message_buffer);
    }

    move_ = SetMovementVector(dir);

    if (!CheckIfMovingPositionIsCorner(dir)) {
        switch (CheckCollision()) {
            case InteractionTypes::MOVE: {
                Move();
                return {InteractionTypes::MOVE, {pos_}};
            }
            case InteractionTypes::FIGHT: {
                return PrepareFightData();
            }
            default: {
                UpdateData data = {InteractionTypes::NONE, {pos_}};
                return data;
            }
        }
    }

    return {InteractionTypes::NONE, {pos_}};
}
