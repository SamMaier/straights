#include <iostream>
#include "Game.h"
#include "TextView.h"
#include <gtkmm.h>


class SampleWindow : public Gtk::Window {
public:
    SampleWindow(): m_button("Sample") {
        set_border_width(10);
        m_button.signal_clicked().connect(sigc::mem_fun(*this, &SampleWindow::onButtonClicked));
        add(m_button);
        m_button.show();
    }
    virtual ~SampleWindow() {};
protected:
    virtual void onButtonClicked() { std::cout << "Button Clicked" << std::endl; };
    Gtk::Button m_button;
};

int main( int argc, char *argv[] ) {

    int seed = 0;
    if ( argc > 1 ) {
        seed = atoi(argv[1]);
    }


    Game* game = new Game(seed);
    GameController* gc = new GameController(game);

    std::cout << (game->getPlayers()->at(3).isHuman() ? "Human" : "Not Human") << std::endl;
    std::cout << game->getCurrentPlayer() << std::endl;
    gc->disablePlayer();
    std::cout << (game->getPlayers()->at(3).isHuman() ? "Human" : "Not Human") << std::endl;
    std::cout << game->getCurrentPlayer() << std::endl;






//    Gtk::Main kit(&argc,&argv);
//    SampleWindow window;
//
//    Gtk::Main::run( window);




    return 0;

}
