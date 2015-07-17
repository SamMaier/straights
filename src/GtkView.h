//
// Created by Shiranka Miskin on 7/12/15.
//

#ifndef STRAIGHTS_GTKVIEW_H
#define STRAIGHTS_GTKVIEW_H

#include <stdlib.h>
#include "Observer.h"
#include "gtkmm.h"
#include <iostream>
#include "Game.h"
#include "ImageFactory.h"
#include "GameController.h"
#include "HandView.h"
#include "PlayersView.h"
#include "Player.h"


const int TABLE_SIZE = RANK_COUNT * SUIT_COUNT;

class GtkView : public Gtk::Window, public Observer {
public:
    GtkView(Game*, GameController*);
    virtual ~GtkView();
    void update();

protected:
    struct GameState {
        std::set<Card> cardsOnTable;
        const std::vector<Player>* players;
        bool isEndOfRound;
        bool isPlaying;
    };


    Game* game_;
    GameController* controller_;
    GameState gameState_;
    bool popUpShown;

    void endOfRoundPopups();
    void onNewGameClicked();
    void onEndGameClicked();
    void queryModel();

    void clearTableImages();
    void setTableImages();

    void startNextRound();

    HandView handView_;
    PlayersView playersView_;

    Gtk::VBox mainBox_;
    Gtk::HBox headerBox_;
    Gtk::Button newGameButton_;
    Gtk::Entry seedTextEntry_;
    Gtk::Button endGameButton_;
    Gtk::Table table_;
    Gtk::Image *cardsOnTable[TABLE_SIZE];
    ImageFactory images_;

};


#endif //STRAIGHTS_GTKVIEW_H
