//
// Created by Shiranka Miskin on 7/12/15.
//

#include "GtkView.h"
#include <sstream>



GtkView::GtkView(Game* game, GameController* controller): game_(game), controller_(controller), popUpShown(true), mainBox_(false, 10), headerBox_(false,10), newGameButton_("New Game"), endGameButton_("End Game"), table_(SUIT_COUNT, RANK_COUNT), handView_(game, controller), playersView_(game, controller){
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

    mainBox_.pack_start(playersView_);
    mainBox_.pack_start(handView_, Gtk::PACK_SHRINK);

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


void GtkView::queryModel() {
    bool isPlaying = game_->isStarted();
    bool isEndOfRound = game_->isEndOfRound();
    std::set<Card> cardsOnTable;
    const std::vector<Player>* players = game_->getPlayers();

    if (isPlaying) {
        cardsOnTable = game_->getTable()->getCards();
    }

    gameState_ = {
            cardsOnTable,
            players,
            isEndOfRound,
            isPlaying
    };
}

void GtkView::endOfRoundPopups() {
    if (!popUpShown) {
        if (gameState_.isEndOfRound || !gameState_.isPlaying) {
            std::cout << std::endl << "End of Round" << std::endl;

            std::stringstream ss;
            for (Player player: *(gameState_.players)) {
                int scoreGained = 0;
                for (Card card : *(player.getDiscards())) {
                    scoreGained += card.getRank() + 1;
                }
                int oldScore = player.getScore() - scoreGained;
                ss << "Player " << player.getName() << "'s discards:" << Card::prettyPrint(*(player.getDiscards())) << std::endl;
                ss << "Player " << player.getName() << "'s score: " << oldScore << " + " << scoreGained << " = " << player.getScore() << std::endl;
            }
            Gtk::MessageDialog dialog( ss.str(), true, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK, true );
            dialog.run();
            popUpShown = true;
            //If the game hasn't ended, ok will just start the next round
            if (gameState_.isPlaying) {
                startNextRound();
                return;
            }
        }
        if (!gameState_.isPlaying) {
            std::cout << std::endl << "End of Game" << std::endl;

            std::stringstream ss;
            ss << "End of Game." << std::endl;
            std::vector<Player*> winners = game_->getWinners();
            if (winners.size() == 1) {
                ss << "The winner is: Player " << winners[0]->getName() << "!";
            } else {
                ss << "The winners are: " << std::endl;
                for (Player* p : winners) {
                    ss << "Player " << p->getName() << "!" << std::endl;
                }
            }

            Gtk::MessageDialog dialog( ss.str(), true, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK, true );
            dialog.run();
            popUpShown = true;
        }
    }
}

void GtkView::startNextRound() {
    popUpShown = false;
    controller_->startNextRound();
}

void GtkView::update() {
    queryModel();
    endOfRoundPopups();
    clearTableImages();
    setTableImages();
}
