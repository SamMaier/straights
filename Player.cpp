#include "Player.h"

Player::Player(int playerNumber) : playerNumber_(playerNumber), score_(0), hand_(nullptr) {};

int Player::getScore() {
    return score_;
}


