//
// Created by Shiranka Miskin on 7/17/15.
//

#include "PlayersView.h"

PlayersView::PlayersView(Game *game, GameController *controller): game_(game), controller_(controller) {
    Gtk::HBox(true, 10);
    game->subscribe(this);


    for (int playerNumber = 0; playerNumber < Game::NUM_PLAYERS; playerNumber++) {
        playerHolders[playerNumber] = Gtk::manage(new Gtk::VBox(true, 10));

        playerFrames[playerNumber] = Gtk::manage(new Gtk::Frame());
        playerFrames[playerNumber]->set_label("Player " + std::to_string(playerNumber + 1));
        playerFrames[playerNumber]->set_label_align(Gtk::ALIGN_LEFT, Gtk::ALIGN_TOP);
        playerFrames[playerNumber]->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

        quitButtons[playerNumber] = Gtk::manage(new Gtk::Button("Make computer"));
        quitButtons[playerNumber]->signal_clicked().connect(
                sigc::bind(sigc::mem_fun(*this, &PlayersView::toggleHumanClicked), playerNumber));

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

}

void PlayersView::queryModel() {

}

void PlayersView::setRageButtons() {

}

void PlayersView::toggleHumanClicked(int playerNumber) {

}

void PlayersView::setScores() {

}
