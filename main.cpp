#include "main.h"

#include "Organism.h"
#include "Animals.h"
#include "WorldManager.h"
#include "Animals/Wolf.h"

int main() {
    WorldManager wm(5, 0);
    // std::vector<std::vector<char> > world_map;
    AnimalData my_data = { WOLF::STR, WOLF::INIT, WOLF::SPRITE };
    Position my_pos2 = { 2, 2 };
    return 0;
}
