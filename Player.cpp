#include "Player.h"

Player::Player(int playerNumber) : hand_(NULL), playerNumber_(playerNumber), score_(0){};


int Player::getScore() {
    return score_;
}

void Player::setHand(const Hand* hand) {
    hand_ = hand;
}

void Player::addScore(int lscore) {
    score_ += score_;
}
