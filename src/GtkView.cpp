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


    for (int card = 0; card < gameState_.hand.size(); card++) {
        cardsInHand[card] = new Gtk::Image(images_.getCardImage(gameState_.hand[card]));
        Gtk::Button *button = new Gtk::Button();
        button->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &GtkView::onCardClicked), gameState_.hand[card])
        );
        button->add(*cardsInHand[card]);
        handBox_.add(*button);
    }

    show_all();
}

void GtkView::onCardClicked(Card c) {
    std::cout << "Card clicked: " << c << std::endl;
}

GtkView::~GtkView() {
}


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

