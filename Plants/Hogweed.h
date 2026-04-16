#ifndef C__1_HOGWEED_H
#define C__1_HOGWEED_H
#include "../Plants.h"


namespace HOGWEED {
    constexpr int STR = 10;
    constexpr char SPRITE = '&';
    constexpr auto TYPE =  OrganismTypes::HOGWEED;
    constexpr int KILL_RADIUS = 1;
}

class Hogweed final: public Plants  {
    static constexpr  PlantData data_ = {
        HOGWEED::STR,
        HOGWEED::SPRITE,
        HOGWEED::TYPE
    };

    bool CheckMapPosValidity(const int x, const int y) const;

    std::vector<Position> LookAround();

public:
    Hogweed(std::vector<std::vector<Organism*> > &world_map,  const Position &spawn_pos) : Plants(world_map, data_, spawn_pos) {}

    UpdateData Update(std::vector<std::string> &message_buffer) override;

    ~Hogweed() override = default;
};


#endif //C__1_HOGWEED_H