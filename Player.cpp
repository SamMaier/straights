#include "Player.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"

Player::Player(int playerNumber, bool isHuman, View* view) : playerNumber_(playerNumber), isHuman_(isHuman), score_(0), hand_(NULL), discards_(NULL), view_(view) {
    if ( isHuman ) {
        strategy_ = new HumanStrategy(view_);
    }
    else {
        strategy_ = new ComputerStrategy();
    }
}

std::string Player::getName() {
    return std::to_string(playerNumber_);
}

Command Player::getPlay(const Table& table) {
    return strategy_->getPlay(*hand_, table);
}

int Player::getScore() {
    return score_;
}

void Player::setHand(const Hand* hand) {
    hand_ = hand;
}

void Player::addScore(int score) {
    score_ += score;
}

void Player::setDiscards(const std::vector<Card>* discards) {
    discards_ = discards;
}

const std::vector<Card> * Player::getDiscards() {
    return discards_;
}

const Hand *Player::getHand() {
    return hand_;
}
