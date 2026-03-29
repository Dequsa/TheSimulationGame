//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ANIMALS_H
#define C__1_ANIMALS_H


#include "Organism.h"

class Animal : public Organism {
private:
    bool CheckCollision();
    void Move();
    bool Collision();
    void Draw();
public:
    Animal(const int &str, const int &init, const std::vector<int>& pos);
    ~Animal() override = default;

    void Update() override;
};


#endif //C__1_ANIMALS_H