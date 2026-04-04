#include "Organism.h"

uint32_t Organism::global_id_counter_ = 0;

Position Organism::ChooseAndSetSpawnPoint() {
    Position pos = {-1, -1};
    const int max_x = static_cast<int>(world_map_[0].size());
    const int max_y = static_cast<int>(world_map_.size());
    int max_tries = MAX_TRIES;
    // (1 --- max_x - 1) <- range of rand so we can do the search with checking neighbors

    while (max_tries--) {
        const int r_x = 1 + rand() % (max_x - 2);
        const int r_y = 1 + rand() % (max_y - 2);

        // check random position if its empty
        if (world_map_[r_y][r_x] == '0') {
            return Position{r_x, r_y};
        }

        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                if (world_map_[r_y + i][r_x + j] == '0') {
                    return Position{r_x + j, r_y + i};
                }
            }
        }
    }
    return pos;
}

// Organism::Organism(std::vector<std::vector<char> > &world_map, const int &str,
//                    const int &init) : world_map_(world_map), str_(str), init_(init) {
//     pos_ = ChooseAndSetSpawnPoint();
//     if (pos_.x == -1 || pos_.y == -1) {
//
//     }
//     id_ = global_id_counter_++;
// }

Position Organism::GetPosition() const {
    return pos_;
}

int Organism::GetStr() const {
    return str_;
}

int Organism::GetInit() const {
    return init_;
}
