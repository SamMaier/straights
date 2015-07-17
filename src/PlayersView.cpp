//
// Created by Shiranka Miskin on 7/17/15.
//

#include "PlayersView.h"

PlayersView::GameState::PlayerInfo::PlayerInfo(std::string name_, int score_, std::vector<Card> discards_, bool isHuman_): name(name_), score(score_), discards(discards_), isHuman(isHuman_) {}

PlayersView::PlayersView(Game *game, GameController *controller): game_(game), controller_(controller) {
    Gtk::HBox(true, 10);
    game->subscribe(this);
    queryModel();

    for (int playerNumber = 0; playerNumber < Game::NUM_PLAYERS; playerNumber++) {
        playerHolders[playerNumber] = Gtk::manage(new Gtk::VBox(true, 10));

        // Style all the frames around the player box
        playerFrames[playerNumber] = Gtk::manage(new Gtk::Frame());
        playerFrames[playerNumber]->set_label("Player " + std::to_string(playerNumber + 1));
        playerFrames[playerNumber]->set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
        playerFrames[playerNumber]->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);


        quitButtons[playerNumber] = Gtk::manage(new Gtk::Button("Make computer"));
        quitButtons[playerNumber]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &PlayersView::toggleHumanClicked), playerNumber));

        // Initialize the text values to 0 as players start with that value
        scoreTexts[playerNumber] = Gtk::manage(new Gtk::Label("Score: 0"));
        discardTexts[playerNumber] = Gtk::manage(new Gtk::Label("Discards: 0"));

        playerHolders[playerNumber]->pack_start(*quitButtons[playerNumber], Gtk::PACK_SHRINK);
        playerHolders[playerNumber]->pack_start(*scoreTexts[playerNumber], Gtk::PACK_SHRINK);
        playerHolders[playerNumber]->pack_start(*discardTexts[playerNumber], Gtk::PACK_SHRINK);

        playerFrames[playerNumber]->add(*playerHolders[playerNumber]);

        add(*playerFrames[playerNumber]);
    }

}

void PlayersView::update() {
    queryModel();
    setScores();
    setRageButtons();
}

void PlayersView::queryModel() {
    bool isPlaying = game_->isStarted();
    int currentPlayer;
    std::vector<GameState::PlayerInfo> playerInfo;

    if (isPlaying) {
        currentPlayer = game_->getCurrentPlayer()->getNumber();
    }

    const std::vector<Player>* players = game_->getPlayers();
    for (const Player & player : *players) {
        GameState::PlayerInfo info = {
                player.getName(),
                player.getScore(),
                isPlaying ? *(player.getDiscards()) : std::vector<Card>(),
                player.isHuman()
        };
        playerInfo.push_back(info);
    }

    gameState_ = {
            currentPlayer,
            playerInfo,
            isPlaying
    };
}

void PlayersView::setRageButtons() {
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

void PlayersView::toggleHumanClicked(int playerNumber) {
    controller_->toggleHuman(playerNumber);
}

void PlayersView::setScores() {
    for (int i = 0; i < Game::NUM_PLAYERS; i++) {
        scoreTexts[i]->set_text("Score: " + std::to_string(gameState_.playerInfo[i].score));
        discardTexts[i]->set_text("Discards: " + std::to_string(gameState_.playerInfo[i].discards.size()));
    }
}

