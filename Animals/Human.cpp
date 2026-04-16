#include "Human.h"
// #include "../WorldManager.h"

DIRECTIONS Human::ChooseDirection(const char key) {
    switch (key) {
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

UpdateData Human::Update() {
    const auto dir = ChooseDirection(current_key_);
    move_ = SetMovementVector(dir);

    if (!CheckIfMovingPositionIsCorner(dir)) {
        switch (CheckCollision()) {
            case InteractionTypes::MOVE: {
                Move();
                return {InteractionTypes::MOVE, {pos_}};
            }
            case InteractionTypes::FIGHT: {
                const auto enemy_pos = pos_ + move_;
                UpdateData data = {InteractionTypes::FIGHT, {pos_, enemy_pos}};
                return data;
            }
            default: {
                UpdateData data = {InteractionTypes::NONE, {pos_}};
                return data;
            }
        }
    }

    return {InteractionTypes::NONE, {pos_}};
}
