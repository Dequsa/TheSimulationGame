#include "main.h"

#include "Organism.h"
#include "Animals.h"
#include "WorldManager.h"
#include "Animals/Wolf.h"

int main() {
    WorldManager wm(5, 2);
    wm.Update();
    wm.Update();
    return 0;
}
