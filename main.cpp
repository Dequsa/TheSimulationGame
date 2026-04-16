#include "main.h"

// char ParseInput(const std::string &input) {
//     switch (input[0]) {
//         case 'a':
//         case 'A':
//             return 'a';
//
//         case 'w':
//         case 'W':
//             return 'w';
//
//         case 's':
//         case 'S':
//             return 's';
//
//         case 'd':
//         case 'D':
//             return 'd';
//
//         case 'x':
//         case 'X':
//             return 'x';
//
//         default:
//             return '\0';
//     }
// }

int main() {
    int map_size = 1;
    int org_num = 1;

    std::cin >> map_size >> org_num;

    // ncruses setup
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    WorldManager wm(map_size, org_num);
    while (true) {
        // std::string input;
        // std::getline(std::cin, input);

        const int input = getch();

        const char key = static_cast<char>(input);

        std::cerr << input << '\n';

        if (key == 'x') {
            break;
        }
        wm.Update(key);
    }
    endwin();
    return 0;
}
