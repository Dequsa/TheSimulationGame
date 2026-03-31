//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ANIMALS_H
#define C__1_ANIMALS_H
#pragma once
#include "Utils.h"
#include "Organism.h"

class Animal : public Organism {
protected:
    bool CheckCollision();

    void Move();

    void Collision();

    void Draw();

public:;
    Animal(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    ~Animal() override = default;

    void Update() override;
};

enum class AnimalTypes {
    WOLF,       // 0
    SHEEP,      // 1
    FOX,        // 2
    TURTLE,     // 3
    ANTELOPE    // 4
};


#endif //C__1_ANIMALS_H
