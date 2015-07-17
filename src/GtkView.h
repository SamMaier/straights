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


const int TABLE_SIZE = RANK_COUNT * SUIT_COUNT;

class GtkView : public Gtk::Window, public Observer {
public:
    GtkView(Game*, GameController*);
    virtual ~GtkView();
    void update();
protected:


    struct GameState {
        int currentPlayer;
        std::set<Card> cardsOnTable;
        struct PlayerInfo {
            PlayerInfo(std::string name, int score, int discards, bool isHuman);
            std::string name;
            int score;
            int discards;
            bool isHuman;
        };
        std::vector<PlayerInfo> playerInfo;
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
    void setScores();
    void setRageButtons();
    void startNextRound();
    void toggleHumanClicked(int playerNumber);

    HandView handView_;

    Gtk::VBox mainBox_;
    Gtk::HBox headerBox_;
    Gtk::Button newGameButton_;
    Gtk::Entry seedTextEntry_;
    Gtk::Button endGameButton_;
    Gtk::HBox playerInfosBox_;
    Gtk::Frame *playerFrames[Game::NUM_PLAYERS];
    Gtk::VBox *playerHolders[Game::NUM_PLAYERS];
    Gtk::Button *quitButtons[Game::NUM_PLAYERS];
    Gtk::Label *scoreTexts[Game::NUM_PLAYERS];
    Gtk::Label *discardTexts[Game::NUM_PLAYERS];
    Gtk::Table table_;
    Gtk::Image *cardsOnTable[TABLE_SIZE];
    ImageFactory images_;

};


#endif //STRAIGHTS_GTKVIEW_H
