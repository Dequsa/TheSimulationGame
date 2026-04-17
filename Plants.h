//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_PLANTS_H
#define C__1_PLANTS_H
#pragma once
#include "Organism.h"

class Plants : public Organism {
public:
    Plants(std::vector<std::vector<Organism*> > &world_map, const PlantData &data, const Position &pos);

    ~Plants() override = default;

    virtual UpdateData Update(std::vector<std::string> &message_buffer) override;

    virtual bool SpecialCheck(Organism &other) override { return false; }

    virtual void SpecialAbility(std::vector<std::string> &message_buffer) override {}

    virtual void Render() override;

    void Print(std::ostream &os) const override;

    virtual InteractionTypes CheckCollision();
};


#endif //C__1_PLANTS_H
