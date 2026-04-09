//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include <iostream>

//
// Animal::Animal(std::vector<std::vector<char> > &world_map, const int &str, const char sprite, const int &init) : Organism(
//     world_map, str, init, sprite) {
// };

// AnimalTypes Animal::GetType() const {
//     switch (sprite_) {
//         case WOLF::SPRITE:
//             return AnimalTypes::WOLF;
//         default:
//             throw std::runtime_error("Unknown animal sprite encountered!");
//             break;
//     }
// }

// Animal *Animal::Update() {
//     UpdateData data{InteractionTypes::MOVE,OrganismTypes::NONE, {{-1, -1}, {-1, -1}}};
//     const auto dir = GetMoveDirection();
//     move_ = SetMovementVector(dir);
//
//     switch (CheckCollision()) {
//         case CollisionTypes::EMPTY: {
//             Move();
//             break;
//         }
//         case CollisionTypes::DIFFERENT_SPECIES: {
//             const auto enemy_pos = pos_ + move_;
//             // Fight(enemy_pos);
//             data = {InteractionTypes::FIGHT,OrganismTypes::NONE, {pos_, enemy_pos}};
//             return this;
//         }
//         case CollisionTypes::SAME_SPECIES: {
//             const auto parent_pos = pos_ + move_;
//
//             data = { InteractionTypes::REPRODUCE ,type_ , {pos_, parent_pos}};
//             is_child = true;
//             return data;
//         }
//         default: {
//             std::cerr << "Unrecognized Collision Type" << '\n';
//             break;
//         }
//     }
//     is_child = false;
//     return data;
// }

UpdateData Animal::Update() {
    UpdateData data{InteractionTypes::MOVE,nullptr, {{-1, -1}, {-1, -1}}};
    const auto dir = GetMoveDirection();
    move_ = SetMovementVector(dir);

    switch (CheckCollision()) {
        case CollisionTypes::EMPTY: {
            Move();
            break;
        }
        case CollisionTypes::DIFFERENT_SPECIES: {
            const auto enemy_pos = pos_ + move_;
            // Fight(enemy_pos);
            data = {InteractionTypes::FIGHT,this, {pos_, enemy_pos}};
            return data;
        }
        case CollisionTypes::SAME_SPECIES: {
            const auto parent_pos = pos_ + move_;

            data = { InteractionTypes::REPRODUCE ,this , {pos_, parent_pos}};
            is_child = true;
            return data;
        }
        default: {
            std::cerr << "Unrecognized Collision Type" << '\n';
            break;
        }
    }
    is_child = false;
    return data;
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

CollisionTypes Animal::CheckCollision() const {
    const auto [x, y] = pos_ + move_;
    const char sprite_on_map = world_map_[y][x];

    if (sprite_on_map == sprite_) {
        return CollisionTypes::SAME_SPECIES;
    }

    if (sprite_on_map == MapSprites::EMPTY) {
        return CollisionTypes::EMPTY;
    }

    return CollisionTypes::DIFFERENT_SPECIES;
}

void Animal::Move() {
    //TODO ADD REPLACING CURRENT TILE WITH #
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
