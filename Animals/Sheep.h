//
// Created by marci on 3/29/2026.
//

#ifndef C__1_SHEEP_H
#define C__1_SHEEP_H
#include "../Animals.h"

namespace SHEEP {
    constexpr int STR = 4;
    constexpr int INIT = 4;
    constexpr char SPRITE = 'S';
}

class Sheep final : public Animal {
    static constexpr AnimalData Sheep_data_ = {
        SHEEP::STR,
        SHEEP::INIT,
        SHEEP::SPRITE,
        OrganismTypes::SHEEP
    };

public:
    Sheep(std::vector<std::vector<Organism*> > &world_map, const Position &spawn_pos) : Animal(
        world_map, Sheep_data_, spawn_pos) {
    }

    ~Sheep() override = default;
};


#endif //C__1_SHEEP_H