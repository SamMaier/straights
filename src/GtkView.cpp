//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_, bool isHuman_): name(name_), score(score_), discards(discards_), isHuman(isHuman_) {}

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

GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), popUpShown(true), mainBox_(false, 10), handBox_(true, 10), headerBox_(false,10), newGameButton_("New Game"), endGameButton_("End Game"), playerInfosBox_(true, 10), table_(SUIT_COUNT, RANK_COUNT){

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

    for (int playerNumber = 0; playerNumber < Game::NUM_PLAYERS; playerNumber++) {
        playerHolders[playerNumber] = Gtk::manage(new Gtk::VBox(true, 10));

        playerFrames[playerNumber] = Gtk::manage(new Gtk::Frame());
        playerFrames[playerNumber]->set_label("Player " + std::to_string(playerNumber + 1));
        playerFrames[playerNumber]->set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
        playerFrames[playerNumber]->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

        quitButtons[playerNumber] = Gtk::manage(new Gtk::Button("Make computer"));
        quitButtons[playerNumber]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &GtkView::toggleHumanClicked), playerNumber));

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
    popUpShown = false;
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
    for (int i = 0; i < HAND_SIZE; i ++ ){
        if (handButtons[i] != NULL)
            delete handButtons[i];     
    }
}


void GtkView::clearTableImages() {
    const Glib::RefPtr<Gdk::Pixbuf> nilCard = images_.getCardImage(NIL_CARD);
    for (int card = 0; card < TABLE_SIZE; card++) {
        cardsOnTable[card]->set(nilCard);
    }
}


void GtkView::clearHandButtons() {
    for (int card = 0; card < HAND_SIZE; card++) {
        if (handButtons[card] != NULL) {
            delete handButtons[card];
            handButtons[card] = NULL;
        }
    }
}


void GtkView::setHandButtons() {

    for (unsigned int card = 0; card < gameState_.hand.size(); card++) {
        Card cardInHand = gameState_.hand[card];


        bool discardable = gameState_.validMoves.size() == 0;
        bool playable = isCardPlayable(gameState_, cardInHand);
        cardsInHand[card] = Gtk::manage(new Gtk::Image(images_.getCardImage(cardInHand)));
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
        handButtons[card] = new Gtk::Button();
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

void GtkView::setScores() {
    for (int i = 0; i < Game::NUM_PLAYERS; i++) {
        scoreTexts[i]->set_text("Score: " + std::to_string(gameState_.playerInfo[i].score));
        discardTexts[i]->set_text("Discards: " + std::to_string(gameState_.playerInfo[i].discards));
    }
}

void GtkView::setRageButtons() {
    if (gameState_.isPlaying) {
        //Only is hit when its a human's turn, thus don't need to bother with computer logic
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            quitButtons[i]->set_label("Ragequit");
            if (i+1 != gameState_.currentPlayer)
                quitButtons[i]->set_sensitive(false);
            else {
                quitButtons[i]->set_sensitive(true);
            }
        }        
    } else {
        for (int i = 0; i < Game::NUM_PLAYERS; i++) {
            quitButtons[i]->set_sensitive(true);
                //set callback
            if (gameState_.playerInfo[i].isHuman) {
                quitButtons[i]->set_label("Make computer");
            } else {
                quitButtons[i]->set_label("Make human");
            }
        }
    }
}

void GtkView::toggleHumanClicked(int playerNumber) {
    controller_->toggleHuman(playerNumber); 
}


void GtkView::queryModel() {
    bool isPlaying = game_->isStarted();
    bool isEndOfRound = game_->isEndOfRound();
    int currentPlayer;
    std::vector<Card> hand;
    std::set<Card> cardsOnTable;
    std::vector<Card> validMoves;
    std::vector<GameState::PlayerInfo> playerInfo;

    if (isPlaying) {
        currentPlayer = game_->getCurrentPlayer()->getNumber();
        hand = game_->getCurrentPlayer()->getHand()->getCards();
        cardsOnTable = game_->getTable()->getCards();
        validMoves = game_->getCurrentPlayer()->getHand()->getValidMoves(cardsOnTable);
    }

    const std::vector<Player>* players = game_->getPlayers();
    for (const Player & player : *players) {
        GameState::PlayerInfo info = {
                player.getName(),
                player.getScore(),
                isPlaying ? (int) player.getDiscards()->size() : 0,
                player.isHuman()
        };
        playerInfo.push_back(info);
    }

    gameState_ = {
            currentPlayer,
            hand,
            cardsOnTable,
            validMoves,
            playerInfo,
            isEndOfRound,
            isPlaying
    };
}

void GtkView::endOfRoundPopups() {
    if (!popUpShown) {
        if (!gameState_.isPlaying) {
            std::cout << "End of Game";

            Gtk::MessageDialog dialog( "End of Game", true, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK, true );
            dialog.run();
            popUpShown = true;
        }
        if (gameState_.isEndOfRound) {
            std::cout << "End of Round";
            Gtk::MessageDialog dialog( "End of Round", true, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK, true );
            dialog.run();
            popUpShown = true;
            startNextRound();
        }
    }
}

void GtkView::startNextRound() {
    popUpShown = false;
    controller_->startNextRound();
}

void GtkView::update() {
    std::cout << "Update!" << std::endl;
    queryModel();
    clearHandButtons();
    endOfRoundPopups();
    setHandButtons();
    clearTableImages();
    setTableImages();
    setScores();
    setRageButtons();
}
