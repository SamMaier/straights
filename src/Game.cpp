//
// Created by Shiranka Miskin on 6/17/15.
//

#include "Game.h"


Player *getMaxScorePlayer(std::vector<Player>* players) {
    int highestScore = players->at(0).getScore();
    Player* highestPlayer = &players->at(0);
    for (Player& player: *players) {
        if (player.getScore() > highestScore) {
            highestScore = player.getScore();
            highestPlayer = &player;
        }
    }
    return highestPlayer;
}

std::vector<Player*> Game::getWinners() {
    int lowestScore = players_.at(0).getScore();
    std::vector<Player*> lowestPlayers;

    // The players with the lowest total score are winners
    for (Player& player: players_) {
        if (player.getScore() < lowestScore) {
            lowestScore = player.getScore();
            lowestPlayers.clear();
            lowestPlayers.push_back(&player);
        } else if (player.getScore() == lowestScore) {
            lowestPlayers.push_back(&player);
        }
    }
    return lowestPlayers;
}

Game::Game(int seed) {
    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_.push_back(Player(player + 1, true));
    }
    running_ = false;
    seed_ = seed;
}

const Deck* Game::getDeck() const{
    return &deck_;
}

const Table *Game::getTable() const{
    return &table_;
}

void Game::toggleHuman(int playerNumber) {
    if (running_) {
        players_[currentPlayer_].ragequit();
        playComputerTurn();
        nextTurn();
        notify();
    } else {
        players_[playerNumber].toggleHuman();
        notify();
    }
}

const std::vector<Player>* Game::getPlayers() const {
    return &players_;
};

void Game::endGame() {
    // going to likely need work
    running_ = false;
    notify();
}

void Game::startGame(int seed) {
    // going to likely need work
    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_[player].resetPlayer();
    }
    seed_ = seed;
    running_ = true;
    deck_ = Deck();
    nextRound();
    notify();
}

bool Game::isStarted() const {
    return running_;
}

void Game::play(Card card) {
    hands_[currentPlayer_].removeCard(card);
    table_.playCard(card);
    notify();
}

void Game::discard(Card card) {
    hands_[currentPlayer_].removeCard(card);
    discards_[currentPlayer_].push_back(card);
    notify();
}

void Game::exit() {
    running_ = false;
    notify();
}

void Game::disablePlayer() {
    players_[currentPlayer_].ragequit();
    playComputerTurn();
    nextTurn();
    notify();
}

void Game::playComputerTurn() {
    Command cmd = players_[currentPlayer_].getPlay(table_);
    switch (cmd.type) {
        case PLAY: play(cmd.card); break;
        case DISCARD: discard(cmd.card); break;
        default: break;
    }
}


void Game::nextTurn() {
    currentPlayer_ = (currentPlayer_ + 1) % NUM_PLAYERS;

    // If the next player is already empty, we've gone through every player's cards
    // since every player loses 1 card each turn
    if (hands_[currentPlayer_].isEmpty()) {

        for (Player& player : players_) {
            int discardScore = 0;
            for (Card discardedCard : *(player.getDiscards()))
                discardScore += discardedCard.getRank() + 1;
            player.addScore(discardScore);
            notify();
        }

        Player* maxScorePlayer = getMaxScorePlayer(&players_);
        if (maxScorePlayer->getScore() >= MAX_SCORE) {
            endGame();
            //just aguess
            notify();
            return;
        } else {
            nextRound();
        }
    }


    if (!players_[currentPlayer_].isHuman()) {
        playComputerTurn();
        nextTurn();
    }

    notify();
}

void Game::nextRound() {

    // Initialize all hands and discard piles to empty
    hands_.clear();
    discards_.clear();
    for (int player = 0; player < NUM_PLAYERS; player++) {
        hands_.push_back(Hand());
        discards_.push_back(std::vector<Card>());
    }

    deck_.shuffle(seed_);

    // Cards assigned as all p players receive the same n number of cards where player 0
    // receives the first n cards, player 1 receives the next n cards, etc.
    for (int deckLocation = 0; deckLocation < Deck::NUM_CARDS; deckLocation++) {

        // The player for each card can now be found easily by dividing by the number of cards per player
        int player = deckLocation / (Deck::NUM_CARDS / NUM_PLAYERS);

        Card card = deck_.getCards()->at(deckLocation);
        hands_[player].addCard(card);

        // The player with the Seven of Spades is the player to go first
        if (card.getRank() == Rank::SEVEN && card.getSuit() == Suit::SPADE)
            currentPlayer_ = player;
    }

    // Let the player know of their hand and discard piles
    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_[player].setHand(&hands_[player]);
        players_[player].setDiscards(&discards_[player]);
    }

    table_.clear();
    notify();

}

bool Game::isValidPlay(const Card& card, const Hand& hand, const Table& table) {
    std::vector<Card> validMoves = hand.getValidMoves(table.getCards());

    return std::find(validMoves.begin(), validMoves.end(), card) != validMoves.end();
}


