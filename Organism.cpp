#include "Organism.h"

uint32_t Organism::global_id_counter_ = 0;

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

OrganismTypes Organism::GetType() const {
    return type_;
}

bool Organism::IsChild() const {
    return child_;
}

void Organism::SetChild(const bool what) {
    child_ = what;
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

void Organism::AgeUp(int n) {
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
