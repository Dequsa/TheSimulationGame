#include "main.h"


struct LoadData {
    int map_size = 1;
    int organism_count = 1;
};

LoadData LoadMapSize(const std::string &map_path) {
    using namespace std;
    fstream map_file(map_path);

    if (!map_file) return {-1, -1};

    std::string size;
    getline(map_file, size);
    istringstream stream(size);

    int map_size = -1;
    int organism_count = -1;
    stream >> map_size >> organism_count;

    if (map_size <= 0 || organism_count < 0) return {-1, -1};

    return {map_size, organism_count};
}

int main() {
    char choice = '\0';
    std::cout << "Load Game: l || Start New Game: any \n";
    std::cin >> choice;

    // load
    int map_size = -1;
    int org_num = -1;
    bool load = false;
    if (choice == 'l') {
        const auto [loaded_size, loaded_count] = LoadMapSize(SAVE_FILE_PATH);
        map_size = loaded_size;
        org_num = loaded_count;
        load = true;
        if (map_size <= 0 || org_num < 0) {
            map_size = 10;
            org_num = 5;
            load = false;
        }
    } else {
        std::cout << "Please enter map size and organism count: \n";
        std::cin >> map_size >> org_num;
    }

    // ncruses setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WorldManager wm(map_size, org_num, load);
    while (true) {
        const int input = getch();

        const char key = static_cast<char>(input);

        std::cerr << input << '\n';

        if (key == 'x') {
            break;
        }
        if (!wm.Update(key)) break;
    }

    keypad(stdscr, FALSE);
    echo();
    nocbreak();
    endwin();

    return 0;
}
