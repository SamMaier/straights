//
// Created by Shiranka Miskin on 7/12/15.
//

#ifndef STRAIGHTS_GTKVIEW_H
#define STRAIGHTS_GTKVIEW_H

#include "Observer.h"
#include "gtkmm.h"
#include <iostream>
#include "Game.h"
#include "ImageFactory.h"


struct GameState {
    std::string currentPlayer;
    std::vector<Card> hand;
    std::set<Card> cardsOnTable;
    std::vector<Card> validMoves;
    struct PlayerInfo {
        PlayerInfo(std::string name, int score, int discards);
        std::string name;
        int score;
        int discards;
    };
    std::vector<PlayerInfo> playerInfo;


};

class GtkView : public Gtk::Window, public Observer {
public:
    GtkView(Game*);
    virtual ~GtkView() {};
    void update();
protected:
    Game* game_;
    GameState gameState_;
    virtual void onButtonClicked();

    Gtk::Button button_;
    Gtk::HBox handBox_;
    Gtk::Frame frame_;
    ImageFactory images_;

};


#endif //STRAIGHTS_GTKVIEW_H
