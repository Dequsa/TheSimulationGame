//
// Created by Kacper Marciniak on 3/11/26.
//

#ifndef C__1_ORGANISM_H
#define C__1_ORGANISM_H
#pragma once
#include <memory>
#include <vector>
#include "Utils.h"

// for animals
struct UpdateData;

class Organism {
protected:
    static uint32_t global_id_counter_;
    std::vector<std::vector<Organism*> > &world_map_;
    Position pos_{};
    uint32_t id_{};
    uint8_t str_{};
    uint8_t init_{};
    int age_{};
    char sprite_{};
    bool has_acted_{};
    bool is_alive_{};
    Position move_;
    OrganismTypes type_{};

public:
    Organism(std::vector<std::vector<Organism*> > &world_map, const AnimalData &data,
             const Position &pos) : world_map_(world_map),
                                    pos_(pos),
                                    str_(data.str),
                                    init_(data.init),
                                    sprite_(data.sprite),
                                    type_(data.type),
                                    has_acted_(true),
                                    is_alive_(true),
                                    move_({0, 0}){
        id_ = global_id_counter_++;
    }

    Organism(std::vector<std::vector<Organism*> > &world_map, const PlantData &data,
             const Position &pos) : world_map_(world_map),
                                    pos_(pos),
                                    str_(data.str),
                                    sprite_(data.sprite),
                                    has_acted_(true),
                                    is_alive_(true),
                                    type_(data.type){
        init_ = 0;
        id_ = global_id_counter_++;
    }

    Organism(const Organism &org) = default;

    virtual ~Organism();

    virtual UpdateData Update() = 0;

    virtual bool SpecialCheck(const Organism &other) const = 0;

    virtual void SpecialAbility() {}

    bool CheckIfMovingPositionIsCorner(const DIRECTIONS dir) const;

    DIRECTIONS GetMoveDirection() const;

    Position SetMovementVector(const DIRECTIONS dir) const;

    void FreeSpace();

    // organism getters
    Position GetPosition() const;

    int GetStr() const;

    int GetInit() const;

    OrganismTypes GetType() const;

    bool GetActivity() const;

    int GetAge() const;

    bool GetLife() const;

    char GetSprite() const;

    // setters
    void SetChild(const bool what);

    void SetActive(const bool what);

    void SetLife(const bool what);

    void SetPosition(const Position &pos);

    void AgeUp(int n);

    // other
    virtual void Render() = 0;
};

struct UpdateData {
    InteractionTypes interaction;
    std::vector<Position> pos;
};

#endif //C__1_ORGANISM_H
