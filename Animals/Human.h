#ifndef C__1_HUMAN_H
#define C__1_HUMAN_H
#include "../Animals.h"

namespace HUMAN{
    constexpr int STR = 3;
    constexpr int INIT = 7;
    constexpr char SPRITE = '@';
    constexpr auto TYPE = OrganismTypes::HUMAN;
}

class Human final : public Animal {
    static constexpr AnimalData data_ = {
        HUMAN::STR,
        HUMAN::INIT,
        HUMAN::SPRITE,
        HUMAN::TYPE
    };

    char current_key_{};

    DIRECTIONS ChooseDirection(const char key);

public:
    Human(std::vector<std::vector<Organism*> > &world_map, const Position &spawn_pos) : Animal(
        world_map, data_, spawn_pos) {
    }

    void SetPlayerInput(const char key) override;

    UpdateData Update() override;

    ~Human() override = default;

    // UpdateData Update(const char key) override;
};

#endif //C__1_HUMAN_H