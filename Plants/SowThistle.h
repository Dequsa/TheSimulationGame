//
// Created by Kacper Marciniak on 4/14/26.
//

#ifndef C__1_SOWTHISTLE_H
#define C__1_SOWTHISTLE_H
#include "../Plants.h"

namespace SOWTHISTLE {
    constexpr int STR = 0;
    constexpr char SPRITE = 'H';
    constexpr auto TYPE =  OrganismTypes::GRASS;
    constexpr int MAX_TRIES = 3;
}

class SowThistle final: public Plants  {
    static constexpr  PlantData data_ = {
        SOWTHISTLE::STR,
        SOWTHISTLE::SPRITE,
        SOWTHISTLE::TYPE
    };
public:
    SowThistle(std::vector<std::vector<Organism*> > &world_map,  const Position &spawn_pos) : Plants(world_map, data_, spawn_pos) {}

    InteractionTypes CheckCollision() override;

    ~SowThistle() override = default;
};


#endif //C__1_SOWTHISTLE_H