//
// Created by marci on 4/10/2026.
//

#include "Utils.h"

std::ostream &operator<<(std::ostream &os, const OrganismTypes type) {
    switch (type) {
        case OrganismTypes::WOLF:      os << "Wolf";        break;
        case OrganismTypes::SHEEP:     os << "Sheep";       break;
        case OrganismTypes::FOX:       os << "Fox";         break;
        case OrganismTypes::TURTLE:    os << "Turtle";      break;
        case OrganismTypes::ANTELOPE:  os << "Antelope";    break;
        case OrganismTypes::NONE:      os << "None";        break;
        default:                       os << "Unknown";     break;
    }
    return os;
}
