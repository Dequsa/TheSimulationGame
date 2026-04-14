//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ANIMALS_H
#define C__1_ANIMALS_H
#pragma once
#include "Utils.h"
#include "Organism.h"

enum class CollisionTypes {
    EMPTY,
    SAME_SPECIES,
    DIFFERENT_SPECIES,
    STAY
};

class WorldManager;

class Animal : public Organism {
protected:

    OrganismTypes GetType() const { return type_; }

    virtual InteractionTypes CheckCollision();

    void Move();

public:;

    Animal(std::vector<std::vector<char> > &world_map, const AnimalData &data,
           const Position &spawn_pos) : Organism(world_map, data, spawn_pos){
    }

    ~Animal() override = default;

    UpdateData Update() override;

    virtual bool SpecialCheck(const Organism &other) const override {return false;}

    virtual void SpecialAbility() override {}

    virtual Position SetMovementVector(const DIRECTIONS dir) {return Organism::SetMovementVector(dir);}

    void Render() override;
};

#endif //C__1_ANIMALS_H
