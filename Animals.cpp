//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>
constexpr uint8_t MAX_TRIES = 9;

Animal::Animal(std::vector<std::vector<char> > &world_map, const int &str, const int &init) : Organism(
    world_map, str, init) {
};

void Animal::Update() {
    // check collision -> move -> draw
    if (CheckCollision()) {
        Collision();
    } else {
        Move();
    }
    Draw();
}

bool Animal::CheckIfMovingPositionIsCorner(const DIRECTIONS dir) {
    const float max_x = static_cast<float>(world_map_.size()) - 1.0f;
    const float max_y = static_cast<float>(world_map_[0].size()) - 1.0f;

    const bool moving_left = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::MID_LEFT || dir == DIRECTIONS::UP_LEFT);
    const bool moving_right = (dir == DIRECTIONS::BOT_RIGHT || dir == DIRECTIONS::MID_RIGHT || dir ==
                               DIRECTIONS::UP_RIGHT);

    const bool moving_up = (dir == DIRECTIONS::UP_LEFT || dir == DIRECTIONS::UP_MID || dir == DIRECTIONS::UP_RIGHT);
    const bool moving_down = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::BOT_MID || dir ==
                              DIRECTIONS::BOT_RIGHT);

    const bool hit_x_edge = (pos_.x <= 0.0f && moving_left) || (pos_.x >= max_x && moving_right);
    const bool hit_y_edge = (pos_.y <= 0.0f && moving_up) || (pos_.y >= max_y && moving_down);

    return hit_x_edge || hit_y_edge;
}

DIRECTIONS Animal::GetMoveDirection() {
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

void Animal::Move() {
    const DIRECTIONS dir = GetMoveDirection();

    switch (dir) {
        case DIRECTIONS::UP_LEFT: {
            pos_.x -= 1;
            pos_.y -= 1;
        }
        case DIRECTIONS::UP_MID: {
            pos_.y -= 1;
        }
        case DIRECTIONS::UP_RIGHT: {
            pos_.x += 1;
            pos_.y -= 1;
        }
        case DIRECTIONS::MID_LEFT: {
            pos_.x -= 1;
        }
        case DIRECTIONS::MID_MID: {
            // STAY ON THE BLOCK
        }
        case DIRECTIONS::MID_RIGHT: {
            pos_.x += 1;
        }
        case DIRECTIONS::BOT_LEFT: {
            pos_.x -= 1;
            pos_.y += 1;
        }
        case DIRECTIONS::BOT_MID: {
            pos_.y += 1;
        }
        case DIRECTIONS::BOT_RIGHT: {
            pos_.x += 1;
            pos_.y += 1;
        }
        default: {
            std::cerr << "Error while trying to move animal: " << id
        }
    }
}

void Animal::Collision() {
}

void Animal::Draw() {
}
