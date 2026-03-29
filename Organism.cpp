//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Organism.h"

Organism::Organism(const int &str, const int &init, const std::vector<int> &pos) {
    str_ = str;
    init_ = init;
    pos_ = pos;
}

Organism::Organism(const Organism &org) {
    str_ = org.str_;
    init_ = org.init_;
    pos_ = org.pos_;
}

std::vector<int> Organism::GetPosition() const {
    return pos_;
}

int Organism::GetStr() {
    return str_;
}

int Organism::GetInit() {
    return init_;
}
