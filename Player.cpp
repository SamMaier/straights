#include "Player.h"

Player::Player(int playerNumber) : hand_(NULL), playerNumber_(playerNumber){};

std::string Player::getName() {
    return std::to_string(playerNumber_);
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
