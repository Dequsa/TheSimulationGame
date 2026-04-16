#include "main.h"


struct LoadData {
    int map_size = 1;
    int organism_count = 1;
};

LoadData LoadMapSize (const std::string &map_path) {
    using namespace std;
    fstream map_file(map_path);

    if (!map_file) return {-1 , -1};

    std::string size;
    getline(map_file, size);
    istringstream stream(size);

    int map_size = -1;
    int organism_count = -1;
    stream >> map_size >> organism_count;

    if (map_size < 0 || organism_count < 0) return {-1 , -1};

    return {map_size, organism_count};

}

int main() {
    char choice = '\0';
    std::cout << "Load Game: l || Start New Game: any \n";
    std::cin >> choice;

    // load
    int map_size = -1;
    int org_num = -1;
    if (choice == 'l') {
        const auto [loaded_size, loaded_count] = LoadMapSize("../Saves/SaveData.txt");
        map_size = loaded_size;
        org_num = loaded_count;
    } else {
        std::cout << "Please enter map size and organism count: \n";
        std::cin >> map_size >> org_num;
    }

    // ncruses setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WorldManager wm(map_size, org_num, choice == 'l');
    while (true) {

        const int input = getch();

        const char key = static_cast<char>(input);

        std::cerr << input << '\n';

        if (key == 'x') {
            break;
        }
        if (!wm.Update(key)) return 0;
    }
    endwin();
    return 0;
}
