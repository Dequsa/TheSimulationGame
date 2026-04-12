//
// Created by marci on 4/10/2026.
//

#include "Utils.h"
#include "Organism.h"

std::ostream &operator<<(std::ostream &os, const OrganismTypes type) {
    switch (type) {
        case OrganismTypes::WOLF: os << "Wolf";
            break;
        case OrganismTypes::SHEEP: os << "Sheep";
            break;
        case OrganismTypes::FOX: os << "Fox";
            break;
        case OrganismTypes::TURTLE: os << "Turtle";
            break;
        case OrganismTypes::ANTELOPE: os << "Antelope";
            break;
        case OrganismTypes::NONE: os << "None";
            break;
        default:
            break;
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const Position &pos) {
    os << "x: " << pos.x << " | y: " << pos.y;
    return os;
}


std::ostream &operator<<(std::ostream &os, const Organism &org) {
    os << org.GetType() << "at position: " << org.GetPosition() << " age: " << org.GetAge() << " str: " << org.GetStr() << " init: " << org.GetInit();
    return os;
}
