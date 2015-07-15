//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_): name(name_), score(score_), discards(discards_) {}


GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), mainBox_(false, 10), handBox_(true, 10), table_(SUIT_COUNT, RANK_COUNT){


    game->subscribe(this);
    queryModel();

    set_border_width(10);

    add(mainBox_);


    frame_.set_label("Your Hand");
    frame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    table_.set_row_spacings(10);
    mainBox_.pack_start(table_, Gtk::PACK_SHRINK);
    const Glib::RefPtr<Gdk::Pixbuf> nilCard = images_.getCardImage(NIL_CARD);
    for (int card = 0; card < SUIT_COUNT * RANK_COUNT; card++) {
        cardsOnTable[card] = new Gtk::Image(nilCard);

        int row = card / RANK_COUNT;
        int column = card % RANK_COUNT;
        table_.attach(*cardsOnTable[card], column, column + 1, row, row + 1);
    }
    setTableImages();

    mainBox_.pack_start(frame_, Gtk::PACK_SHRINK);
    frame_.add(handBox_);

    setHandButtons();

    show_all();
}

void GtkView::onCardClicked(Card c) {
    std::cout << "Card clicked: " << c << std::endl;
    controller_->play(c);
}

GtkView::~GtkView() {
}


void GtkView::clearTableImages() {
    const Glib::RefPtr<Gdk::Pixbuf> nilCard = images_.getCardImage(NIL_CARD);
    for (int card = 0; card < TABLE_SIZE; card++) {
        cardsOnTable[card]->set(nilCard);
    }
}


void GtkView::clearHandButtons() {
    for (int card = 0; card < HAND_SIZE; card++) {
        if (handButtons[card] != NULL)
            delete handButtons[card];
        handButtons[card] = new Gtk::Button();
    }
}



void GtkView::setHandButtons() {
    clearHandButtons();
    for (int card = 0; card < gameState_.hand.size(); card++) {
        cardsInHand[card] = new Gtk::Image(images_.getCardImage(gameState_.hand[card]));
            handButtons[card] = new Gtk::Button();
        handButtons[card]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &GtkView::onCardClicked), gameState_.hand[card])
        );
        handButtons[card]->add(*cardsInHand[card]);
        handBox_.add(*handButtons[card]);
    }

    for (int card = gameState_.hand.size(); card < HAND_SIZE; card++) {
        handBox_.add(*handButtons[card]);
    }
    show_all();
}

void GtkView::setTableImages() {
    for (Card c : gameState_.cardsOnTable) {
        int index = c.getSuit() * RANK_COUNT + c.getRank();
        cardsOnTable[index]->set(images_.getCardImage(c));
    }
}


void GtkView::queryModel() {
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


void GtkView::update() {
    std::cout << "Update!" << std::endl;
    queryModel();
    setHandButtons();
    clearTableImages();
    setTableImages();
}

