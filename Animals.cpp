//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>

Animal::~Animal() {
    world_map_[pos_.y][pos_.x] = MapSprites::EMPTY;
}

UpdateData Animal::Update() {
    age_++;
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

            child_ = true;

            data = { InteractionTypes::REPRODUCE, {pos_, parent_pos}};
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

    // grow up
    if (child_) child_ = false;

    return data;
}

void Animal::SetPosition(const Position &pos) {
    world_map_[pos_.y][pos_.x] = MapSprites::EMPTY;
    Organism::SetPosition(pos);
}

void Animal::Render() {
    world_map_[pos_.y][pos_.x] = sprite_;
}

bool Animal::CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const {
    const int max_x = world_map_.size() - 1;
    const int max_y = world_map_[0].size() - 1;

    const bool moving_left = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::MID_LEFT || dir == DIRECTIONS::UP_LEFT);
    const bool moving_right = (dir == DIRECTIONS::BOT_RIGHT || dir == DIRECTIONS::MID_RIGHT || dir ==
                               DIRECTIONS::UP_RIGHT);

    const bool moving_up = (dir == DIRECTIONS::UP_LEFT || dir == DIRECTIONS::UP_MID || dir == DIRECTIONS::UP_RIGHT);
    const bool moving_down = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::BOT_MID || dir ==
                              DIRECTIONS::BOT_RIGHT);

    const bool hit_x_edge = (pos_.x <= 0 && moving_left) || (pos_.x >= max_x && moving_right);
    const bool hit_y_edge = (pos_.y <= 0 && moving_up) || (pos_.y >= max_y && moving_down);

    return hit_x_edge || hit_y_edge;
}

InteractionTypes Animal::CheckCollision() {
    const auto [x, y] = pos_ + move_;

    if (x == -1 || y == -1) {
        // they dont actually move they just dont do anything updatey
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

DIRECTIONS Animal::GetMoveDirection() const {
    DIRECTIONS valid_moves[9];
    int valid_count = 0;
    for (int i = 0; i < static_cast<int>(DIRECTIONS::DIR_COUNT); i++) {
        auto temp = static_cast<DIRECTIONS>(i);
        if (!CheckIfMovingPositionIsCorner(temp)) {
            valid_moves[valid_count] = temp;
            valid_count++;
        }
    }

    if (valid_count == 0) return DIRECTIONS::MID_MID;

    return valid_moves[rand() % valid_count];
}

Position Animal::SetMovementVector(const DIRECTIONS dir) {
    // const DIRECTIONS dir = GetMoveDirection();
    Position move = {0, 0};
    switch (dir) {
        case DIRECTIONS::UP_LEFT: {
            move.x -= 1;
            move.y -= 1;
            break;
        }
        case DIRECTIONS::UP_MID: {
            move.y -= 1;
            break;
        }
        case DIRECTIONS::UP_RIGHT: {
            move.x += 1;
            move.y -= 1;
            break;
        }
        case DIRECTIONS::MID_LEFT: {
            move.x -= 1;
            break;
        }
        case DIRECTIONS::MID_MID: {
            // STAY ON THE BLOCK
            break;
        }
        case DIRECTIONS::MID_RIGHT: {
            move.x += 1;
            break;
        }
        case DIRECTIONS::BOT_LEFT: {
            move.x -= 1;
            move.y += 1;
            break;
        }
        case DIRECTIONS::BOT_MID: {
            move.y += 1;
            break;
        }
        case DIRECTIONS::BOT_RIGHT: {
            move.x += 1;
            move.y += 1;
            break;
        }
        default: {
            std::cerr << "Error while trying to set movement vector for animal id: " << id_ << '\n';
        }
    }
    return move;
}
