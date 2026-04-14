#include "Organism.h"

uint32_t Organism::global_id_counter_ = 0;

bool Organism::CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const {
    const int max_x = world_map_.size() - 1;
    const int max_y = world_map_[0].size() - 1;

    const bool moving_left = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::MID_LEFT || dir == DIRECTIONS::UP_LEFT);
    const bool moving_right = (dir == DIRECTIONS::BOT_RIGHT || dir == DIRECTIONS::MID_RIGHT || dir == DIRECTIONS::UP_RIGHT);

    const bool moving_up = (dir == DIRECTIONS::UP_LEFT || dir == DIRECTIONS::UP_MID || dir == DIRECTIONS::UP_RIGHT);
    const bool moving_down = (dir == DIRECTIONS::BOT_LEFT || dir == DIRECTIONS::BOT_MID || dir == DIRECTIONS::BOT_RIGHT);

    const bool hit_x_edge = (pos_.x <= 0 && moving_left) || (pos_.x >= max_x && moving_right);
    const bool hit_y_edge = (pos_.y <= 0 && moving_up) || (pos_.y >= max_y && moving_down);

    return hit_x_edge || hit_y_edge;
}

DIRECTIONS Organism::GetMoveDirection() const {
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


Position Organism::GetPosition() const {
    return pos_;
}

int Organism::GetStr() const {
    return str_;
}

int Organism::GetInit() const {
    return init_;
}

OrganismTypes Organism::GetType() const {
    return type_;
}

void Organism::SetActive(const bool what) {
    has_acted_ = what;
}

void Organism::SetLife(const bool what) {
    is_alive_ = what;
}

void Organism::SetPosition(const Position &pos) {
    world_map_[pos_.y][pos_.x] = MapSprites::EMPTY;
    pos_ = pos;
    world_map_[pos_.y][pos_.x] = sprite_;
}

void Organism::AgeUp(const int n) {
    age_ += n;
}

bool Organism::GetActivity() const {
    return has_acted_;
}

int Organism::GetAge() const {
    return age_;
}

bool Organism::GetLife() const {
    return is_alive_;
}

Position Organism::SetMovementVector(const DIRECTIONS dir) const {
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
