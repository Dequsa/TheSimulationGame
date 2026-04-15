#include "main.h"

int main() {
    int map_size = 1, org_num = 1;
    std::cin >> map_size >> org_num;
    std::string input;
    WorldManager wm(map_size, org_num);
    std::getline(std::cin, input);
    do {
        wm.Update();
        std::getline(std::cin, input);
    } while (input != "END");
    return 0;
}
