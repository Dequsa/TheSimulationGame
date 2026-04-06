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
    DIFFERENT_SPECIES
};

enum class AnimalTypes {
    WOLF, // 0
    SHEEP, // 1
    FOX, // 2
    TURTLE, // 3
    ANTELOPE // 4
};

struct AnimalData {
    const int str;
    const int init;
    const char sprite;
    const AnimalTypes type;
};

class Animal : public Organism {
    Position move_;

    bool CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const;

    DIRECTIONS GetMoveDirection() const;

    AnimalTypes GetType() const;

protected:
    AnimalTypes type_{};

    void Reproduce(Position parent_pos);

    CollisionTypes CheckCollision() const;

    void Move();

    Position SetMovementVector(const DIRECTIONS dir) const;

    void Draw();

public:;

    //Animal(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    Animal(std::vector<std::vector<char> > &world_map, const AnimalData &data, const Position &spawn_pos) :
    Organism(world_map, data, spawn_pos),
        type_(data.type) {
    }

    ~Animal() override = default;

    void Update(WorldManager &wm) override;

    void Update() override {
    };
};

#endif //C__1_ANIMALS_H
