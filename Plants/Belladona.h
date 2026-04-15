//
// Created by Kacper Marciniak on 4/15/26.
//

#ifndef C__1_BELLADONA_H
#define C__1_BELLADONA_H
#include "../Plants.h"

namespace BELLADONNA {
    constexpr int STR = 99;
    constexpr char SPRITE = 'B';
    constexpr auto TYPE =  OrganismTypes::BELLADONNA;
    constexpr int STR_INCREASE = 1;
}

class Belladonna final : public Plants {
    static constexpr  PlantData data_ = {
        BELLADONNA::STR,
        BELLADONNA::SPRITE,
        BELLADONNA::TYPE
    };
public:
    Belladonna(std::vector<std::vector<Organism*> > &world_map,  const Position &spawn_pos) : Plants(world_map, data_, spawn_pos) {}

    bool SpecialCheck(Organism &other) override;

    ~Belladonna() override = default;
};

#endif //C__1_BELLADONA_H