//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"

bool Animal::CheckCollision() {

}

Animal::Animal(std::vector<std::vector<char> > &world_map, const int &str, const int &init) : Organism(world_map, str, init) {
};

void Animal::Update() {
    // move -> check collision -> draw
    Move();
    if (CheckCollision()) {
        Collision();
    }
    Draw();
}

void Animal::Move() {
    // uint8_t dir = ;
}

void Animal::Collision() {
}

void Animal::Draw() {
}
