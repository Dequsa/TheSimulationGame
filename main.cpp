#include "main.h"

#include "Organism.h"
#include "Animals.h"
#include "WorldManager.h"
#include "Animals/Wolf.h"

int main() {
    WorldManager wm(5, 1);
    wm.SpawnAnimals(OrganismTypes::WOLF, {0, 0});
    wm.Update();
    return 0;
}
