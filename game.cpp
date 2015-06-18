//
// Created by Shiranka Miskin on 6/17/15.
//

#include "game.h"

Game::Game(int seed) {
    /*players_.reserve(NUM_PLAYERS);
    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_.at(player);
    }*/
    currentRound_ = -1;
    running_ = true;


}

void Game::play(Card card) {
    hands_[currentPlayer_].removeCard(card);
    table_.playCard(card);
}

void Game::discard(Card card) {
    hands_[currentPlayer_].removeCard(card);
    table_.discardCard(card);
}

void Game::exit() {
    running_ = false;
}

void Game::disablePlayer() {

}

void Game::nextTurn() {
    currentPlayer_ = (currentPlayer_ + 1) % NUM_PLAYERS;
}

void Game::nextRound() {

    hands_.clear();
    hands_.reserve(NUM_PLAYERS);
    for (int deckLocation = 0; deckLocation < Deck::NUM_CARDS; deckLocation++) {
        int player = deckLocation / NUM_PLAYERS;
        Card card = deck_.getCards()->at(deckLocation);
        hands_[player].addCard(card);

        if (card.getRank() == Rank::SEVEN && card.getSuit() == Suit::SPADE)
            currentPlayer_ = player;
    }

    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_[player].setHand(&hands_[player]);
    }

    table_.clear();
    currentRound_++;

}

void Game::run() {
    int maxScore = 0;
    while (running_) {
        while (maxScore < 80) {
            Command command = players_[currentPlayer_].getPlay(table_);
            switch(command.type) {
                case Type::PLAY:
                    play(command.card);
                    break;
                case Type::DISCARD:
                    discard(command.card);
                    break;
                case Type::RAGEQUIT:
                    disablePlayer();
                    break;
                case Type::QUIT:
                    exit();
                    break;
                case Type::DECK:


                    break;
                default:
                    break;

            }
        }
    }



}
