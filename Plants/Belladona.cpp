//
// Created by Kacper Marciniak on 4/15/26.
//

#include "Belladona.h"

bool Belladonna::SpecialCheck(Organism &other) {
    AddStr(other.GetStr() + BELLADONNA::STR_INCREASE);
    return false;
}
