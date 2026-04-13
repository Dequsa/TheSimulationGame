#include "main.h"

int main() {
    int map_size = 1, org_num = 1;
    std::cin >> map_size >> org_num;
    std::string input;
    WorldManager wm(map_size, org_num);
    do {
        std::getline(std::cin, input);
        wm.Update();
    } while (input != "END");
    return 0;
}
