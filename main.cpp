#include <iostream>
#include "__tests__.h"
#include "Game.h"
#include "TextView.h"


int main( int argc, char *argv[] ) {

    int seed = 0;
    if ( argc > 1 ) {
        seed = atoi(argv[1]);
    }

    View* view = new TextView();

    Game game(seed, view);
    game.run();

}
		