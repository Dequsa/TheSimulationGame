#include "Organism.h"

uint32_t Organism::global_id_counter_ = 0;

Organism::~Organism() {
    world_map_[pos_.y][pos_.x] = nullptr;
}

bool Organism::CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const {
    // 1. Fixed the swapped X and Y axis bounds
    const int max_x = world_map_[0].size() - 1;
    const int max_y = world_map_.size() - 1;

    const auto [x, y] = SetMovementVector(dir);
    const int target_x = pos_.x + x;
    const int target_y = pos_.y + y;

    const bool hit_x_edge = (target_x < 0) || (target_x > max_x);
    const bool hit_y_edge = (target_y < 0) || (target_y > max_y);

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
    world_map_[pos_.y][pos_.x] = nullptr;
    pos_ = pos;
    world_map_[pos_.y][pos_.x] = this;
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

char Organism::GetSprite() const {
    return sprite_;
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

void Organism::FreeSpace() {
    world_map_[pos_.y][pos_.x] = nullptr;
}
