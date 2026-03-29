//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ANIMALS_H
#define C__1_ANIMALS_H
#pragma once
#include "Utils.h"
#include "Organism.h"

class Animal : public Organism {
private:
    bool CheckCollision();

    void Move();

    bool Collision();

    void Draw();

public:
    Animal(const int &str, const int &init, const Position &pos);

    ~Animal() override = default;

    void Update() override;
};

enum class AnimalTypes {
    WOLF,
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE
};


#endif //C__1_ANIMALS_H
