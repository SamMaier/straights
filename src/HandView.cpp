//
// Created by Shiranka Miskin on 7/17/15.
//

#include "HandView.h"

Gdk::Color getColor(int r = 0, int g = 0, int b = 0) {
    Gdk::Color color;
    color.set_rgb(r << 8,g << 8,b << 8);
    return color;
}

const Gdk::Color GREEN = getColor(31, 209, 55);
const Gdk::Color LIGHT_GREEN = getColor(46, 242,72);
const Gdk::Color RED = getColor(252, 137, 124);
const Gdk::Color LIGHT_RED = getColor(255, 186, 179);
const Gdk::Color YELLOW = getColor(242, 213, 46);
const Gdk::Color LIGHT_YELLOW = getColor(231, 240, 72);

bool HandView::isCardPlayable(GameState* state, Card card) {
    return std::find(state->validMoves.begin(), state->validMoves.end(), card) != state->validMoves.end();
}


HandView::HandView(Game *game, GameController *controller): game_(game), controller_(controller), handBox_(true, 10) {
    game->subscribe(this);
    queryModel();


    set_label("Your Hand");
    set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    add(handBox_);

    setHandButtons();
}

void HandView::clearHandButtons() {
    for (int card = 0; card < HAND_SIZE; card++) {
        if (handButtons_[card] != NULL)
            delete handButtons_[card];
    }
}

void HandView::setHandButtons() {
    for (unsigned int card = 0; card < gameState_.hand.size(); card++) {
        Card cardInHand = gameState_.hand[card];


        bool discardable = gameState_.validMoves.size() == 0;
        bool playable = isCardPlayable(&gameState_, cardInHand);
        cardsInHand_[card] = Gtk::manage(new Gtk::Image(images_.getCardImage(cardInHand)));
        Gtk::Button* button = Gtk::manage(new Gtk::Button());
        Glib::RefPtr<Gtk::Style> style = button->get_style()->copy();
        style->set_bg(Gtk::STATE_NORMAL, discardable ? YELLOW : (playable ? GREEN : RED));
        style->set_bg(Gtk::STATE_PRELIGHT, discardable ? LIGHT_YELLOW : (playable ? LIGHT_GREEN : LIGHT_RED));
        button->set_style(style);
        handButtons_[card] = button;


        handButtons_[card]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &HandView::onCardClicked), cardInHand)
        );
        handButtons_[card]->add(*cardsInHand_[card]);
        handBox_.add(*handButtons_[card]);
    }

    for (int card = gameState_.hand.size(); card < HAND_SIZE; card++) {
        handButtons_[card] = Gtk::manage(new Gtk::Button());
        handButtons_[card]->add(*Gtk::manage(new Gtk::Image(images_.getCardImage(NIL_CARD))));
        handBox_.add(*handButtons_[card]);
    }

    show_all();
}

void HandView::onCardClicked(Card card) {
    if (gameState_.validMoves.size() == 0)
        controller_->discard(card);
    else if (isCardPlayable(&gameState_, card))
        controller_->play(card);
}

void HandView::queryModel() {
    bool isPlaying = game_->isStarted();
    std::vector<Card> hand;
    std::vector<Card> validMoves;

    if (isPlaying) {
        hand = game_->getCurrentPlayer()->getHand()->getCards();
        validMoves = game_->getCurrentPlayer()->getHand()->getValidMoves(game_->getTable()->getCards());
    }

    gameState_ = {
            hand,
            validMoves
    };
}


void HandView::update() {
    queryModel();
    clearHandButtons();
    setHandButtons();
}
