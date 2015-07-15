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
    GtkView(Game*, GameController*);
    virtual ~GtkView();
    void update();
protected:
    Game* game_;
    GameController* controller_;
    GameState gameState_;
    void onCardClicked(Card);
    void onNewGameClicked();
    void onEndGameClicked();
    void queryModel();
    void clearHandButtons();
    void setHandButtons();
    void setTableImages();

    Gtk::Button button_;
    Gtk::VBox mainBox_;
    Gtk::HBox handBox_;
    Gtk::HBox headerBox_;
    Gtk::Button newGameButton_;
    Gtk::Entry seedTextEntry_;
    Gtk::Button endGameButton_;
    Gtk::Image *cardsInHand[RANK_COUNT * SUIT_COUNT / Game::NUM_PLAYERS];
    Gtk::Button *handButtons[RANK_COUNT * SUIT_COUNT / Game::NUM_PLAYERS];
    Gtk::Frame frame_;
    Gtk::Table table_;
    Gtk::Image *cardsOnTable[RANK_COUNT * SUIT_COUNT];
    ImageFactory images_;

};


#endif //STRAIGHTS_GTKVIEW_H
