//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_): name(name_), score(score_), discards(discards_) {}


GtkView::GtkView(Game* game): game_(game), handBox_(true, 10){

    update();

    const Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = images_.getCardImage(Card(SPADE, Rank::THREE));


    set_border_width(10);
    frame_.set_label("Your Hand");
    frame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    add(frame_);
//
    frame_.add(handBox_);
    for (int i = 0; i < SUIT_COUNT * RANK_COUNT + 1; i++) {
        cards_[i] = new Gtk::Image(images_.getCardImage(i));
    }


    for (Card card : gameState_.hand) {
        handBox_.add(*cards_[card.getSuit() * RANK_COUNT + card.getRank()]);
    }

    show_all();
}

GtkView::~GtkView() {
    for (int i = 0; i < 4; i++) {
        delete cards_[i];
    }
}

void GtkView::onButtonClicked() {
  std::cout << "Button Clicked" << std::endl;
};

void GtkView::update() {
    std::string currentPlayer = game_->getCurrentPlayer()->getName();
    std::vector<Card> hand = game_->getCurrentPlayer()->getHand()->getCards();
    std::set<Card> cardsOnTable = game_->getTable()->getCards();
    std::vector<Card> validMoves = game_->getCurrentPlayer()->getHand()->getValidMoves(cardsOnTable);
    std::vector<GameState::PlayerInfo> playerInfo;

    const std::vector<Player>* players = game_->getPlayers();
    for (const Player & player : *players) {
        GameState::PlayerInfo info = {
                player.getName(),
                player.getScore(),
                (int) player.getDiscards()->size()
        };
        playerInfo.push_back(info);
    }

    gameState_ = {
            currentPlayer,
            hand,
            cardsOnTable,
            validMoves,
            playerInfo
    };
}

