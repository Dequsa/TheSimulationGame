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
    std::vector<std::vector<char> > &world_map_;
    Position pos_{};
    uint32_t id_{};
    uint8_t str_{};
    uint8_t init_{};
    int age_{};
    char sprite_{};
    bool child_{};
    bool has_acted_{};
    OrganismTypes type_{};

public:
    // Organism(std::vector<std::vector<char> > &world_map, const int &str, const int &init);

    Organism(std::vector<std::vector<char> > &world_map, const AnimalData &data,
             const Position &pos) : world_map_(world_map),
                                    pos_(pos),
                                    str_(data.str),
                                    init_(data.init),
                                    sprite_(data.sprite),
                                    type_(data.type),
                                    child_(true),
                                    has_acted_(true){
        id_ = global_id_counter_++;
    }

    Organism(const Organism &org) = default;

    virtual ~Organism() = default;

    virtual UpdateData Update() = 0;

    virtual bool SpecialCheck(const Organism &other) const = 0;

    virtual void SpecialAbility() {}

    // organism getters
    Position GetPosition() const;

    int GetStr() const;

    int GetInit() const;

    OrganismTypes GetType() const;

    bool IsChild() const;

    bool GetActivity() const;

    int GetAge() const;


    // setters
    void SetChild(const bool what);

    void SetActive(const bool what);

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
