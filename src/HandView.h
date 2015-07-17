//
// Created by Shiranka Miskin on 7/17/15.
//

#ifndef STRAIGHTS_HANDVIEW_H
#define STRAIGHTS_HANDVIEW_H

#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include "Card.h"
#include "Game.h"
#include "GameController.h"
#include "ImageFactory.h"

const int MAX_HAND_SIZE = RANK_COUNT * SUIT_COUNT / Game::NUM_PLAYERS;



class HandView:public Gtk::Frame, public Observer {
public:
    HandView(Game*, GameController*);
    void update();
private:

    struct GameState {
        std::vector<Card> hand;
        std::vector<Card> validMoves;
    };

    Game* game_;
    GameController* controller_;
    Gtk::HBox handBox_;
    void onCardClicked(Card);
    void clearHandButtons();
    void setHandButtons();
    Gtk::Image *cardsInHand_[MAX_HAND_SIZE];
    Gtk::Button *handButtons_[MAX_HAND_SIZE];
    ImageFactory images_;
    GameState gameState_;
    void queryModel();
    bool isCardPlayable(GameState*, Card);
};


#endif //STRAIGHTS_HANDVIEW_H
