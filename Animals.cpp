//
// Created by Kacper Marciniak on 3/11/26.
//

#include "Animals.h"

bool Animal::CheckCollision() {

}

Animal::Animal(const int &str, const int &init, const Position & pos) : Organism(str, init, pos) {};

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

bool Animal::Collision() {
}

void Animal::Draw() {
}
