#ifndef C__1_HUMAN_H
#define C__1_HUMAN_H
#include "../Animals.h"

namespace HUMAN{
    constexpr int STR = 3;
    constexpr int INIT = 7;
    constexpr char SPRITE = '@';
    constexpr auto TYPE = OrganismTypes::HUMAN;
    constexpr int POTION_STR = 5;
}

class Human final : public Animal {
    static constexpr AnimalData data_ = {
        HUMAN::STR,
        HUMAN::INIT,
        HUMAN::SPRITE,
        HUMAN::TYPE
    };

    bool has_buffed_ = false;
    int buff_time_ = 0;
    char current_key_{};

    DIRECTIONS HandleInput(const char key);

    void BuffDecay();

    bool BuffCheck(const DIRECTIONS dir);

    UpdateData PrepareFightData();

public:
    Human(std::vector<std::vector<Organism*> > &world_map, const Position &spawn_pos) : Animal(
        world_map, data_, spawn_pos) {
    }

    void SpecialAbility( std::vector<std::string> &message_buffer) override;

    void SetPlayerInput(const char key) override;

    UpdateData Update(std::vector<std::string> &message_buffer) override;

    ~Human() override = default;

    // UpdateData Update(const char key) override;
};

#endif //C__1_HUMAN_H