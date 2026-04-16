#include "Hogweed.h"

bool Hogweed::CheckMapPosValidity(const int x, const int y) const {

    if (x < 0 || y < 0) {
        return false;
    }

    if (x >= world_map_[0].size() || y >= world_map_.size()) {
        return false;
    }

    if ( world_map_[y][x] == nullptr  || world_map_[y][x]->GetType() == type_ ) {
        return false;
    }

    return true;
}

std::vector<Position> Hogweed::LookAround() {
    std::vector<Position> result;

    for (int i = -HOGWEED::KILL_RADIUS; i <= HOGWEED::KILL_RADIUS; i++) { // x
        for (int j = -HOGWEED::KILL_RADIUS; j <= HOGWEED::KILL_RADIUS; j++) { // y
            const auto x = i + pos_.x;
            const auto y = j + pos_.y;

            if (i == 0 && j == 0) continue;

            if (!CheckMapPosValidity(x, y)) continue;

            result.push_back(Position{x, y});
        }
    }
    return result;
}

UpdateData Hogweed::Update() {
    // auto data = Plants::Update();

    const std::vector<Position> dead = LookAround();

    if (dead.empty()) {
        return Plants::Update();
    }

    UpdateData data = {InteractionTypes::AOE_KILL, dead};
    return data;
}
