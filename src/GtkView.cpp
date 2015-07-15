//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_): name(name_), score(score_), discards(discards_) {}

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

bool isCardPlayable(GameState state, Card card) {
    return std::find(state.validMoves.begin(), state.validMoves.end(), card) != state.validMoves.end();
}


GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), mainBox_(false, 10), handBox_(true, 10), headerBox_(false,10), newGameButton_("New Game"), endGameButton_("End Game"), table_(SUIT_COUNT, RANK_COUNT) {

    game->subscribe(this);
    queryModel();

    set_border_width(10);

    add(mainBox_);

    frame_.set_label("Your Hand");
    frame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    mainBox_.pack_start(headerBox_, Gtk::PACK_SHRINK);
    // add initial value of 0 seedTextEntry_();
    newGameButton_.signal_clicked().connect(
            sigc::mem_fun(*this, &GtkView::onNewGameClicked));
    endGameButton_.signal_clicked().connect(
            sigc::mem_fun(*this, &GtkView::onEndGameClicked));
    headerBox_.add(newGameButton_); headerBox_.add(seedTextEntry_); headerBox_.add(endGameButton_);


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

    clearHandButtons();
    setHandButtons();

    show_all();

}

void GtkView::onNewGameClicked() {
    std::cout << "New game hit." << std::endl;
    int seed = atoi(seedTextEntry_.get_text().c_str());
    controller_->startGame(seed);
}

void GtkView::onEndGameClicked() {
    std::cout << "End game hit." << std::endl;
    controller_->endGame();
}

void GtkView::onCardClicked(Card c) {
    std::cout << "Card clicked: " << c << std::endl;

    if (gameState_.validMoves.size() == 0)
        controller_->discard(c);
    else if (isCardPlayable(gameState_, c))
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
        Card cardInHand = gameState_.hand[card];


        bool discardable = gameState_.validMoves.size() == 0;
        bool playable = isCardPlayable(gameState_, cardInHand);
        cardsInHand[card] = new Gtk::Image(images_.getCardImage(cardInHand));
        Gtk::Button* button = new Gtk::Button();
        Glib::RefPtr<Gtk::Style> style = button->get_style()->copy();
        style->set_bg(Gtk::STATE_NORMAL, discardable ? YELLOW : (playable ? GREEN : RED));
        style->set_bg(Gtk::STATE_PRELIGHT, discardable ? LIGHT_YELLOW : (playable ? LIGHT_GREEN : LIGHT_RED));
        button->set_style(style);
        handButtons[card] = button;

        
        handButtons[card]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &GtkView::onCardClicked), cardInHand)
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
