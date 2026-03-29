//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Organism.h"

Position Organism::ChooseAndSetSpawnPoint() {
    Position pos =  {0, 0};

    for (int i = 0; i < world_map_->size(); i++) {
        for (int j = 0; j < world_map_->at(i).size(); j++) {
            if (world_map_->at(i).at(j) == '#') {
                pos.x = static_cast<float>(i);
                pos.y = static_cast<float>(i);
            }
        }
    }
    return pos;
}

Organism::Organism(const WorldManager &wm, const int &str, const int &init) {
    world_map_ = wm.GetWorldMap();
    str_ = str;
    init_ = init;
    pos_ = ChooseAndSetSpawnPoint();
}

Organism::Organism(const int &str, const int &init, const Position &pos) {
    str_ = str;
    init_ = init;
    pos_ = pos;
}

Organism::Organism(const Organism &org) {
    str_ = org.str_;
    init_ = org.init_;
    pos_ = org.pos_;
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
