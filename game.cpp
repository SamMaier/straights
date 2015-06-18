//
// Created by Shiranka Miskin on 6/17/15.
//

#include "game.h"

Game::Game(int seed) {
    scores_.reserve(NUM_PLAYERS);
    for (int player = 0; player < NUM_PLAYERS; player++) {
        scores_.at(player) = 0;
    }
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
    for (int i = 0; i < Deck::NUM_CARDS; i++) {
        int player = i / NUM_PLAYERS;
        Card card = deck_.getCards()->at(i);
        hands_[player].addCard(card);

        if (card.getRank() == Rank::SEVEN && card.getSuit() == Suit::SPADE)
            currentPlayer_ = player;
    }

    table_.clear();
    currentRound_++;

}

void Game::run() {
    int maxScore = 0;
    while (running_) {
        while (maxScore < 80) {

        }
    }



}
