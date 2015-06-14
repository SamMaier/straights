#include <iostream>
#include "__tests__.h"


int main( int argc, char *argv[] ) {
    int seed = 0;
    if ( argc > 1 ) {
        seed = atoi(argv[1]);
    }
    /*
    bool players[4];
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << std::endl;
        std::string input;
        std::cout << ">";
        std::cin >> input;
        players[i] = input == "h";
    }

    for (int i = 0; i < 4; i++) {
        std::cout << (players[i] ? "Human" : "Computer") << std::endl;
    }
    */

    Test::printTable();
}
		