//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Organism.h"

Position Organism::ChooseAndSetSpawnPoint() {
    Position pos = {0, 0};
    const int max_x = static_cast<int>(world_map_[0].size());
    const int max_y = static_cast<int>(world_map_.size());
    int max_tries = world_map_[0].size();
    // (1 --- max_x - 1) <- range of rand so we can do the search with checking neighbors

    while (max_tries--) {
        const int r_x = 1 + rand() % (max_x - 1);
        const int r_y = 1 + rand() % (max_y - 1);

        // check random position if its empty
        if (world_map_[r_y][r_x] == '0') {
            pos.x = r_x;
            pos.y = r_y;
            return pos;
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (world_map_[r_y + i][r_x + j] == '0') {
                    pos.x = static_cast<float>(r_x + i);
                    pos.y = static_cast<float>(r_y + j);
                    return pos;
                }
            }
        }
    }
}

Organism::Organism(std::vector<std::vector<char> > &world_map, const int &str,
                   const int &init) : str_(str), init_(init), world_map_(world_map) {
    pos_ = ChooseAndSetSpawnPoint();
}

Organism::Organism(std::vector<std::vector<char> > &world_map, const int &str, const int &init, const Position &pos)
    : pos_(pos),
      str_(str),
      init_(init),
      world_map_(world_map) {
}

Position Organism::GetPosition() const {
    return pos_;
}

int Organism::GetStr() {
    return str_;
}

int Organism::GetInit() {
    return init_;
}
