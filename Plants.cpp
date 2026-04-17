//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Plants.h"

Plants::Plants(std::vector<std::vector<Organism*> > &world_map, const PlantData &data, const Position &pos) : Organism(
    world_map, data, pos) {
}

UpdateData Plants::Update(std::vector<std::string> &message_buffer) {
    UpdateData data{InteractionTypes::MOVE, {{-1, -1}, {-1, -1}}};
    const auto dir = GetMoveDirection();
    move_ = SetMovementVector(dir);
    switch (CheckCollision()) {
        case InteractionTypes::REPRODUCE: {
            if (move_.x == 0 && move_.y == 0) {
                data.interaction = InteractionTypes::MOVE;
                break;
            }

            data = {InteractionTypes::REPRODUCE, {pos_}};

            break;
        }
        case InteractionTypes::NONE: {
            data.interaction = InteractionTypes::MOVE;
            break;
        }
        default: {
            std::cerr << "Unrecognized Interaction Type" << '\n';
            break;
        }
    }

    return data;
}

void Plants::Render() {
    world_map_[pos_.y][pos_.x] = this;
}

void Plants::Print(std::ostream &os) const {
        os << GetType() << " at position: " << GetPosition() << " age: " << GetAge();
}

InteractionTypes Plants::CheckCollision() {
    const auto [x, y] = pos_ + move_;

    if (x < 0 || y < 0 || y >= world_map_.size() || x >= world_map_[0].size()) {
        return InteractionTypes::NONE;
    }

    const Organism *target = world_map_[y][x];

    if (target == nullptr) {
        // 12.5% chance to sow
        if ((rand() & 7) == 0)  {
            // 0111 = 7 (1/2 * 1/2 * 1/2)
            return InteractionTypes::REPRODUCE;
        }
    }

    return InteractionTypes::NONE;
}
