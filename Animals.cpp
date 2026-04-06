//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>
#include "Animals/Wolf.h"
constexpr uint8_t MAX_TRIES = 9;

//
// Animal::Animal(std::vector<std::vector<char> > &world_map, const int &str, const char sprite, const int &init) : Organism(
//     world_map, str, init, sprite) {
// };

AnimalTypes Animal::GetType() const {
    switch (sprite_) {
        case WOLF::SPRITE:
            return AnimalTypes::WOLF;
    }
}

void Animal::Update() {
    // check collision -> move -> draw
    switch (CheckCollision()) {
        case CollisionTypes::EMPTY: {
            Move();
        }
        case CollisionTypes::DIFFERENT_SPECIES: {
            const auto enemy_pos = pos_ + move_;
            // Fight(enemy_pos);
        }
        case CollisionTypes::SAME_SPECIES: {
            struct data {
                uint8_t type;
                Position pos;
            } data{};
            const auto type = GetType();
            const auto parent_pos = pos_ + move_;
        }
        default: {
        }
    }
    Draw();
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


void Animal::Reproduce(Position parent_pos) {
}

CollisionTypes Animal::CheckCollision() const {
    const auto check_pos = pos_ + move_;
    const char sprite_on_map = world_map_[check_pos.x][check_pos.y];

    if (sprite_on_map == sprite_) {
        return CollisionTypes::SAME_SPECIES;
    }

    if (sprite_on_map == MapSprites::EMPTY) {
        return CollisionTypes::EMPTY;
    }

    return CollisionTypes::DIFFERENT_SPECIES;
}

void Animal::Move() {
    const auto dir = GetMoveDirection();
    move_ = SetMovementVector(dir);
    pos_ += move_;
}

DIRECTIONS Animal::GetMoveDirection() const {
    DIRECTIONS valid_moves[9];
    int valid_count = 0;
    for (int i = 0; i < static_cast<int>(DIRECTIONS::DIR_COUNT); i++) {
        auto temp = static_cast<DIRECTIONS>(i);
        if (!CheckIfMovingPositionIsCorner(temp)) {
            valid_moves[i] = temp;
            valid_count++;
        }
    }

    if (valid_count == 0) return DIRECTIONS::MID_MID;

    return valid_moves[rand() % valid_count];
}

Position Animal::SetMovementVector(const DIRECTIONS dir) const {
    // const DIRECTIONS dir = GetMoveDirection();
    Position move = {0, 0};
    switch (dir) {
        case DIRECTIONS::UP_LEFT: {
            move.x -= 1;
            move.y -= 1;
        }
        case DIRECTIONS::UP_MID: {
            move.y -= 1;
        }
        case DIRECTIONS::UP_RIGHT: {
            move.x += 1;
            move.y -= 1;
        }
        case DIRECTIONS::MID_LEFT: {
            move.x -= 1;
        }
        case DIRECTIONS::MID_MID: {
            // STAY ON THE BLOCK
        }
        case DIRECTIONS::MID_RIGHT: {
            move.x += 1;
        }
        case DIRECTIONS::BOT_LEFT: {
            move.x -= 1;
            move.y += 1;
        }
        case DIRECTIONS::BOT_MID: {
            move.y += 1;
        }
        case DIRECTIONS::BOT_RIGHT: {
            move.x += 1;
            move.y += 1;
        }
        default: {
            std::cerr << "Error while trying to set movement vector for animal id: " << id_ << '\n';
        }

            return move;
    }
}

void Animal::Draw() {
}
