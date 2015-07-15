#include <iostream>
#include "Game.h"
#include "TextView.h"
#include <gtkmm.h>
#include "GtkView.h"



void printCardSet(std::set<Card> cardSet) {
    std::vector<Card> cards;
    std::copy(cardSet.begin(), cardSet.end(), std::back_inserter(cards));
    std::cout << "Cards: " << Card::prettyPrint(cards) << std::endl;
}

void printState(Game* game) {

    const std::vector<Player>* players = game->getPlayers();
    for (const Player & player : *players) {
        std::cout << "Player " << player.getName()  << " (" << (player.isHuman() ? "Human" : "Computer") << ")" << std::endl;
        std::cout << "      Score: " << player.getScore() << std::endl;
        std::cout << "      Cards: " << Card::prettyPrint(player.getHand()->getCards()) << std::endl;
    }

    std::cout << "Cards on the table:" << std::endl;
    std::cout << *game->getTable() << std::endl;
}

int main( int argc, char *argv[] ) {


//    Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file("res/0_0.png");

    int seed = 0;
    if ( argc > 1 ) {
        seed = atoi(argv[1]);
    }

    Game* game = new Game(seed);
    GameController* controller = new GameController(game);

    controller->disablePlayer();
    controller->disablePlayer();
    controller->disablePlayer();
    printState(game);

   Gtk::Main kit(&argc,&argv);
   GtkView window(game, controller);

   Gtk::Main::run( window);
    printState(game);

    return 0;

}
