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


Player *getMinScorePlayer(std::vector<Player>* players) {
    int lowestScore = players->at(0).getScore();
    Player* lowestPlayer = &players->at(0);
    for (Player& player: *players) {
        if (player.getScore() < lowestScore) {
            lowestScore = player.getScore();
            lowestPlayer = &player;
        }
    }
    return lowestPlayer;
}

Game::Game(int seed, View* view) {
    for (int player = 0; player < NUM_PLAYERS; player++) {
//        bool human = view->checkIfHuman(std::to_string(player + 1));
    }
    currentRound_ = -1;
    running_ = true;
    view_ = view;
}

const Deck* Game::getDeck() {
    return &deck_;
}

const Table *Game::getTable() {
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
    view_->alertGameEnd(&players_[0]); // TODO: Make real winner
}

void Game::disablePlayer() {
    view_->alertRagequit(&players_[currentPlayer_]);
}


void Game::nextTurn() {
    if (hands_[currentPlayer_].isEmpty()) {
        Player* player = &players_[currentPlayer_];
        int oldScore = player->getScore();
        int discardScore = 0;
        for (Card discardedCard : *(player->getDiscards()))
            discardScore += discardedCard.getRank() + 1;
        player->addScore(discardScore);
        view_->alertEmptyHand(player, oldScore);
    }


    currentPlayer_ = (currentPlayer_ + 1) % NUM_PLAYERS;
    // if the next player is already empty, we've gone through every player's cards
    if (hands_[currentPlayer_].isEmpty()) {
        Player* maxScorePlayer = getMaxScorePlayer(&players_);
        if (maxScorePlayer->getScore() >= MAX_SCORE) {
            view_->alertGameEnd(getMinScorePlayer(&players_));
            exit();
            return;
        }
        nextRound();
    }
}

void Game::nextRound() {

    hands_.clear();
    discards_.clear();
    hands_.reserve(NUM_PLAYERS);
    discards_.reserve(NUM_PLAYERS);
    for (int deckLocation = 0; deckLocation < Deck::NUM_CARDS; deckLocation++) {
        int player = deckLocation / NUM_PLAYERS;
        Card card = deck_.getCards()->at(deckLocation);
        hands_[player].addCard(card);

        if (card.getRank() == Rank::SEVEN && card.getSuit() == Suit::SPADE)
            currentPlayer_ = player;
    }

    for (int player = 0; player < NUM_PLAYERS; player++) {
        players_[player].setHand(&hands_[player]);
        players_[player].setDiscards(&discards_[player]);
    }

    table_.clear();
    currentRound_++;

    view_->alertBeginRound(&players_[currentPlayer_]);

}

bool Game::isValidPlay(const Card& card, const Hand& hand, const Table& table) {
    std::vector<Card> validMoves = hand.getValidMoves(table.getCardsOnBoard());

    if (std::find(validMoves.begin(), validMoves.end(), card) != validMoves.end()) {
        return true;
    } else {
        return false;
    }
}

void Game::run() {
    while (running_) {
        Command command = players_[currentPlayer_].getPlay(table_);
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
                break;
            default:
                break;
        }
    }
}


