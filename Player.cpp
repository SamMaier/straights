#include "Player.h"

Player::Player(int playerNumber) : playerNumber_(playerNumber), score_(0), hand_(NULL) {};

int Player::getScore() {
    return score_;
}

void Player::setHand(const Hand* hand) {
    hand_ = hand;
}

