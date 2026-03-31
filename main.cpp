#include "main.h"

#include "Organism.h"
#include "Animals.h"

int main() {
    std::vector<std::vector<char> > world_map;
    Animal Animal(world_map, 2, 3);
    Animal.Update();
    return 0;
}
