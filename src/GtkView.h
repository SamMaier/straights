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
#include "GameController.h"




const int HAND_SIZE = RANK_COUNT * SUIT_COUNT / Game::NUM_PLAYERS;
const int TABLE_SIZE = RANK_COUNT * SUIT_COUNT;

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
    void queryModel();
    void clearHandButtons();
    void setHandButtons();
    void clearTableImages();
    void setTableImages();

    Gtk::Button button_;
    Gtk::VBox mainBox_;
    Gtk::HBox handBox_;
    Gtk::Image *cardsInHand[HAND_SIZE];
    Gtk::Button *handButtons[HAND_SIZE];
    Gtk::Frame frame_;
    Gtk::Table table_;
    Gtk::Image *cardsOnTable[TABLE_SIZE];
    ImageFactory images_;

};


#endif //STRAIGHTS_GTKVIEW_H
