//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>

Animal::~Animal() {
    world_map_[pos_.y][pos_.x] = MapSprites::EMPTY;
}

UpdateData Animal::Update() {
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

            data = { InteractionTypes::REPRODUCE, {pos_, parent_pos}};

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
    world_map_[pos_.y][pos_.x] = sprite_;
}

InteractionTypes Animal::CheckCollision() {
    const auto [x, y] = pos_ + move_;

    if (x == -1 || y == -1) {
        return InteractionTypes::NONE;
    }

    const char sprite_on_map = world_map_[y][x];

    if (sprite_on_map == sprite_) {
        return InteractionTypes::REPRODUCE;
    }

    if (sprite_on_map == MapSprites::EMPTY) {
        return InteractionTypes::MOVE;
    }

    return InteractionTypes::FIGHT;
}

void Animal::Move() {
    world_map_[pos_.y][pos_.x] = MapSprites::EMPTY;
    pos_ += move_;
    world_map_[pos_.y][pos_.x] = sprite_;
}