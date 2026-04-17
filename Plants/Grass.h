//
// Created by Kacper Marciniak on 4/14/26.
//

#ifndef C__1_GRASS_H
#define C__1_GRASS_H
#include "../Utils.h"
#include "../Plants.h"
namespace GRASS {
    constexpr int STR = 0;
    constexpr char SPRITE = '_';
    constexpr auto TYPE =  OrganismTypes::GRASS;
}

class Grass final : public Plants {
    static constexpr  PlantData data_ = {
        GRASS::STR,
        GRASS::SPRITE,
        GRASS::TYPE
    };
    public:
    Grass(std::vector<std::vector<Organism*> > &world_map,  const Position &spawn_pos) : Plants(world_map, data_, spawn_pos) {}
    ~Grass() override = default;
};


#endif //C__1_GRASS_H