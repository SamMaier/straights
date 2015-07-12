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

std::vector<Player*> getWinners(std::vector<Player>* players) {
    int lowestScore = players->at(0).getScore();
    std::vector<Player*> lowestPlayers;

    // The players with the lowest total score are winners
    for (Player& player: *players) {
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

Game::Game(int seed, View* view) {
    for (int player = 0; player < NUM_PLAYERS; player++) {
        bool isHuman = view->checkIfHuman(std::to_string(player + 1));
        players_.push_back(Player(player + 1, isHuman, view));
    }
    running_ = true;
    view_ = view;
    seed_ = seed;
    nextRound();
}

const Deck* Game::getDeck() const{
    return &deck_;
}

const Table *Game::getTable() const{
    return &table_;
}

void Game::play(Card card) {
    hands_[currentPlayer_].removeCard(card);
    table_.playCard(card);
    view_->alertPlayedCard(&players_[currentPlayer_], card);
}

void Game::discard(Card card) {
    hands_[currentPlayer_].removeCard(card);
    discards_[currentPlayer_].push_back(card);
    view_->alertDiscardCard(&players_[currentPlayer_], card);
}

void Game::exit() {
    running_ = false;
}

void Game::disablePlayer() {
    players_[currentPlayer_].ragequit();
    view_->alertRagequit(&players_[currentPlayer_]);
}

void endRoundSummary(std::vector<Player>& players, View* view) {
    for (Player& player : players) {
        int oldScore = player.getScore();
        int discardScore = 0;
        for (Card discardedCard : *(player.getDiscards()))
            discardScore += discardedCard.getRank() + 1;
        player.addScore(discardScore);
        view->alertEmptyHand(&player, oldScore);
    }
}


void Game::nextTurn() {
    currentPlayer_ = (currentPlayer_ + 1) % NUM_PLAYERS;
    // If the next player is already empty, we've gone through every player's cards
    // since every player loses 1 card each turn
    if (hands_[currentPlayer_].isEmpty()) {
        endRoundSummary(players_, view_);
        Player* maxScorePlayer = getMaxScorePlayer(&players_);
        if (maxScorePlayer->getScore() >= MAX_SCORE) {
            std::vector<Player*> winners = getWinners(&players_);
            for (Player* player : winners)
                view_->alertGameEnd(player);
            exit();
            return;
        }
        nextRound();
    }
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

    view_->alertBeginRound(&players_[currentPlayer_]);

}

bool Game::isValidPlay(const Card& card, const Hand& hand, const Table& table) {
    std::vector<Card> validMoves = hand.getValidMoves(table.getCardsOnBoard());

    return std::find(validMoves.begin(), validMoves.end(), card) != validMoves.end();
}

void Game::run() {

    // Keep track of if the last command was the deck being printed
    // to avoid the players acting as if they hadn't just asked for a play
    // ex: a Human player strategy will print the current table when it first asks for a play
    bool deckHasPrinted = false;
    while (running_) {

        if (!deckHasPrinted)
            players_[currentPlayer_].alertPlay(table_);
        Command command = players_[currentPlayer_].getPlay(table_);
        deckHasPrinted = false;

        // A turn is only consumed if a player Plays or Discards a card
        switch (command.type) {
            case Type::PLAY:
                play(command.card);
                nextTurn();
                break;
            case Type::DISCARD:
                discard(command.card);
                nextTurn();
                break;
            case Type::RAGEQUIT:
                disablePlayer();
                break;
            case Type::QUIT:
                exit();
                break;
            case Type::DECK:
                view_->alertDeck(&deck_);
                deckHasPrinted = true;
                break;
            default:
                break;
        }
    }
}


