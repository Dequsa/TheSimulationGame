//
// Created by Kacper Marciniak on 4/15/26.
//

#include "Guarana.h"

bool Guarana::SpecialCheck(Organism &other) {
    other.AddStr(GUARANA::STR_INCREASE);
    return false;
}
