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
    Position move_;

    bool CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const;

    DIRECTIONS GetMoveDirection() const;

protected:
    OrganismTypes GetType() const { return type_; }

    InteractionTypes CheckCollision() const;

    void Move();

    Position SetMovementVector(const DIRECTIONS dir) const;

public:;

    //Animal(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    Animal(std::vector<std::vector<char> > &world_map, const AnimalData &data,
           const Position &spawn_pos) : Organism(world_map, data, spawn_pos){
    }

    ~Animal() override = default;

    UpdateData Update() override;

    void Render() override;
};

#endif //C__1_ANIMALS_H
