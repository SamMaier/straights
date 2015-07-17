//
// Created by Shiranka Miskin on 7/17/15.
//

#ifndef STRAIGHTS_PLAYERSVIEW_H
#define STRAIGHTS_PLAYERSVIEW_H


#include <gtkmm.h>
#include "Observer.h"
#include "GameController.h"

class PlayersView: public Gtk::HBox, public Observer {
public:
    PlayersView(Game*, GameController*);
    void update();
private:

    void setScores();
    void setRageButtons();
    void toggleHumanClicked(int playerNumber);

    struct GameState {
        int currentPlayer;
        struct PlayerInfo {
            PlayerInfo(std::string name, int score, std::vector<Card> discards, bool isHuman);
            std::string name;
            int score;
            std::vector<Card> discards;
            bool isHuman;
        };
        std::vector<PlayerInfo> playerInfo;
        bool isPlaying;
    };

    Gtk::Frame *playerFrames[Game::NUM_PLAYERS];
    Gtk::VBox *playerHolders[Game::NUM_PLAYERS];
    Gtk::Button *quitButtons[Game::NUM_PLAYERS];
    Gtk::Label *scoreTexts[Game::NUM_PLAYERS];
    Gtk::Label *discardTexts[Game::NUM_PLAYERS];

    Game* game_;
    GameController* controller_;
    GameState gameState_;
    void queryModel();
};


#endif //STRAIGHTS_PLAYERSVIEW_H
