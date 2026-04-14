//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_PLANTS_H
#define C__1_PLANTS_H
#pragma once
#include "Organism.h"

class Plants : public Organism {
public:
    Plants(std::vector<std::vector<char> > &world_map, const PlantData &data, const Position &pos);

    ~Plants() override = default;

    virtual UpdateData Update() override;

    virtual bool SpecialCheck(const Organism &other) const override { return false; };

    virtual void SpecialAbility() override {}

    virtual void Render() override;

    InteractionTypes CheckCollision();
};


#endif //C__1_PLANTS_H
