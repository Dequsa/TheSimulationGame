//
// Created by Kacper Marciniak on 4/15/26.
//

#ifndef C__1_GUARANA_H
#define C__1_GUARANA_H
#include "../Plants.h"

namespace GUARANA {
    constexpr int STR = 0;
    constexpr char SPRITE = '^';
    constexpr auto TYPE =  OrganismTypes::GUARANA;
    constexpr int STR_INCREASE = 3;
}

class Guarana final : public Plants {
    static constexpr  PlantData data_ = {
        GUARANA::STR,
        GUARANA::SPRITE,
        GUARANA::TYPE
    };
    public:
    Guarana(std::vector<std::vector<Organism*> > &world_map,  const Position &spawn_pos) : Plants(world_map, data_, spawn_pos) {}

    bool SpecialCheck(Organism &other) override;

    ~Guarana() override = default;
};


#endif //C__1_GUARANA_H