//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>

UpdateData Animal::Update(std::vector<std::string> &message_buffer) {
    UpdateData data{InteractionTypes::MOVE, {{-1, -1}, {-1, -1}}};
    const auto dir = GetMoveDirection();
    move_ = SetMovementVector(dir);

    switch (CheckCollision()) {
        case InteractionTypes::MOVE: {
            Move();
            break;
        }
        case InteractionTypes::FIGHT: {
            const auto enemy_pos = pos_ + move_;
            // Fight(enemy_pos);
            data = {InteractionTypes::FIGHT, {pos_, enemy_pos}};
            return data;
        }
        case InteractionTypes::REPRODUCE: {
            if (move_.x == 0 && move_.y == 0) {
                data.interaction = InteractionTypes::MOVE;
                return data;
            }

            const auto parent_pos = pos_ + move_;

            data = {InteractionTypes::REPRODUCE, {pos_, parent_pos}};

            move_ = SetMovementVector(DIRECTIONS::MID_MID);
            return data;
        }
        case InteractionTypes::NONE: {
            data.interaction = InteractionTypes::MOVE;
            return data;
        }
        default: {
            std::cerr << "Unrecognized Collision Type" << '\n';
            break;
        }
    }

    return data;
}

void Animal::Render() {
    world_map_[pos_.y][pos_.x] = this;
}

InteractionTypes Animal::CheckCollision() {
    const auto [x, y] = pos_ + move_;

    // if animal wants to go out of bounds stop them
    if (x < 0 || y < 0 || y >= world_map_.size() || x >= world_map_[0].size()) {
        return InteractionTypes::NONE;
    }

    const Organism *target = world_map_[y][x];

    if (target == nullptr) {
        return InteractionTypes::MOVE;
    }

    if (target->GetType() == type_) {
        return InteractionTypes::REPRODUCE;
    }

    return InteractionTypes::FIGHT;
}

void Animal::Move() {
    world_map_[pos_.y][pos_.x] = nullptr;
    pos_ += move_;
    world_map_[pos_.y][pos_.x] = this;
}

void Animal::MoveToPosition(const Position &pos) {
    world_map_[pos_.y][pos_.x] = nullptr;
    pos_ = pos;
    world_map_[pos_.y][pos_.x] = this;
    move_ = {0, 0   };
}
