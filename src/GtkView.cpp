//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_): name(name_), score(score_), discards(discards_) {}


GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), mainBox_(false, 10), handBox_(true, 10), playerInfosBox_(true, 10), headerBox_(false,10), newGameButton_("New Game"), endGameButton_("End Game"), table_(SUIT_COUNT, RANK_COUNT){


    game->subscribe(this);
    queryModel();

    set_border_width(10);

    add(mainBox_);


    frame_.set_label("Your Hand");
    frame_.set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
    frame_.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    mainBox_.pack_start(headerBox_, Gtk::PACK_SHRINK);
    seedTextEntry_.set_text("0");
    newGameButton_.signal_clicked().connect(
            sigc::mem_fun(*this, &GtkView::onNewGameClicked));
    endGameButton_.signal_clicked().connect(
            sigc::mem_fun(*this, &GtkView::onEndGameClicked));
    headerBox_.add(newGameButton_);
    headerBox_.add(seedTextEntry_);
    headerBox_.add(endGameButton_);


    table_.set_row_spacings(10);
    mainBox_.pack_start(table_, Gtk::PACK_SHRINK);
    const Glib::RefPtr<Gdk::Pixbuf> nilCard = images_.getCardImage(NIL_CARD);
    for (int card = 0; card < SUIT_COUNT * RANK_COUNT; card++) {
        cardsOnTable[card] = Gtk::manage(new Gtk::Image(nilCard));

        int row = card / RANK_COUNT;
        int column = card % RANK_COUNT;
        table_.attach(*cardsOnTable[card], column, column + 1, row, row + 1);
    }
    setTableImages();

    for (int playerNumber = 1; playerNumber <= Game::NUM_PLAYERS; playerNumber++) {
        playerHolders[playerNumber] = Gtk::manage(new Gtk::VBox(true, 10));

        playerFrames[playerNumber] = Gtk::manage(new Gtk::Frame());
        playerFrames[playerNumber]->set_label("Player " + std::to_string(playerNumber));
        playerFrames[playerNumber]->set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
        playerFrames[playerNumber]->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

        quitButtons[playerNumber] = Gtk::manage(new Gtk::Button("Human"));
        //tie this to a function

        scoreTexts[playerNumber] = Gtk::manage(new Gtk::Label("Score: 0"));

        discardTexts[playerNumber] = Gtk::manage(new Gtk::Label("Discards: 0"));
        
        playerHolders[playerNumber]->pack_start(*quitButtons[playerNumber], Gtk::PACK_SHRINK);
        playerHolders[playerNumber]->pack_start(*scoreTexts[playerNumber], Gtk::PACK_SHRINK);
        playerHolders[playerNumber]->pack_start(*discardTexts[playerNumber], Gtk::PACK_SHRINK);

        playerFrames[playerNumber]->add(*playerHolders[playerNumber]);

        playerInfosBox_.add(*playerFrames[playerNumber]);
    }
    mainBox_.pack_start(playerInfosBox_, Gtk::PACK_SHRINK);

    mainBox_.pack_start(frame_, Gtk::PACK_SHRINK);
    frame_.add(handBox_);

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
    controller_->play(c);
}

GtkView::~GtkView() {
/*
    for (int i = 0; i < HAND_SIZE; i ++ ){
        delete cardsInHand[i];     
        delete handButtons[i];     
    }
    for (int i = 0; i < Game::NUM_PLAYERS; i ++ ){
        delete quitButtons[i];     
        delete scoreTexts[i];     
        delete discardTexts[i];     
        delete playerHolders[i];     
        delete playerFrames[i];     
    }
    for (int i = 0; i < TABLE_SIZE; i ++ ){
        delete cardsOnTable[i];
    }
*/
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
    }
}



void GtkView::setHandButtons() {

    for (int card = 0; card < gameState_.hand.size(); card++) {
            cardsInHand[card] = Gtk::manage(new Gtk::Image(images_.getCardImage(gameState_.hand[card])));
            handButtons[card] = Gtk::manage(new Gtk::Button());
            handButtons[card]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &GtkView::onCardClicked), gameState_.hand[card])
        );
        handButtons[card]->add(*cardsInHand[card]);
        handBox_.add(*handButtons[card]);
    }

    for (int card = gameState_.hand.size(); card < HAND_SIZE; card++) {
        handButtons[card] = Gtk::manage(new Gtk::Button());
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
    clearHandButtons();
    setHandButtons();
    clearTableImages();
    setTableImages();
}

