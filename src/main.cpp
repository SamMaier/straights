#include <gtkmm.h>
#include "Game.h"
#include "GtkView.h"



int main( int argc, char *argv[] ) {

    int seed = 0;
    if ( argc > 1 ) {
        seed = atoi(argv[1]);
    }

    Game* game = new Game(seed);
    GameController* controller = new GameController(game);


    Gtk::Main kit(&argc,&argv);
    GtkView window(game, controller);

    Gtk::Main::run( window);

    return 0;

}
