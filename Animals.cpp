//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"
#include "utility.h"
bool Animal::CheckCollision() {
    return true;
}

Animal::Animal(const int &str, const int &init, const std::vector<int>& pos) : Organism(str, init, pos) {};

void Animal::Update() {
    // move -> check collision -> draw
    Move();
    if (CheckCollision()) {
        Collision();
    }
    Draw();
}

void Animal::Move() {
    uint8_t dir = UniversalFn::GenerateRandomNumber();
}

bool Animal::Collision() {
}

void Animal::Draw() {
}
