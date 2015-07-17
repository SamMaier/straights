//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"

GtkView::GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, int discards_, bool isHuman_): name(name_), score(score_), discards(discards_), isHuman(isHuman_) {}

GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), mainBox_(false, 10), headerBox_(false,10), newGameButton_("New Game"), endGameButton_("End Game"), playerInfosBox_(true, 10), table_(SUIT_COUNT, RANK_COUNT), handView_(game, controller){

    game->subscribe(this);
    queryModel();

    set_border_width(10);

    add(mainBox_);

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
    mainBox_.pack_start(handView_, Gtk::PACK_SHRINK);

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

GtkView::~GtkView() {
}


void GtkView::clearTableImages() {
    const Glib::RefPtr<Gdk::Pixbuf> nilCard = images_.getCardImage(NIL_CARD);
    for (int card = 0; card < TABLE_SIZE; card++) {
        cardsOnTable[card]->set(nilCard);
    }
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
    int currentPlayer;
    std::set<Card> cardsOnTable;
    std::vector<GameState::PlayerInfo> playerInfo;

    if (isPlaying) {
        currentPlayer = game_->getCurrentPlayer()->getNumber();
        cardsOnTable = game_->getTable()->getCards();
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
            cardsOnTable,
            playerInfo,
            isPlaying
    };
}


void GtkView::update() {
    queryModel();
    clearTableImages();
    setTableImages();
    setScores();
    setRageButtons();
}
