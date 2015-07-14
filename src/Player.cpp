#include "Player.h"
#include "HumanStrategy.h"
#include "ComputerStrategy.h"

Player::Player(int playerNumber, bool isHuman) : playerNumber_(playerNumber), score_(0),
    hand_(NULL), discards_(NULL), isHuman_(isHuman) {
    if ( isHuman_ ) {
        strategy_ = new HumanStrategy();
    }
    else {
        strategy_ = new ComputerStrategy();
    }
}

std::string Player::getName() const {
    return std::to_string(playerNumber_);
}

Command Player::getPlay(const Table& table) const {
    return strategy_->getPlay(*hand_, table);
}

void Player::alertPlay(const Table& table) const {
    strategy_->alertPlay(*hand_, table);
}

int Player::getScore() const {
    return score_;
}

void Player::setHand(const Hand* hand) {
    hand_ = hand;
}

void Player::addScore(int score) {
    score_ += score;
}

void Player::ragequit() {
    if (isHuman_) {
        delete strategy_;
        strategy_ = new ComputerStrategy();
        isHuman_ = false;
    }
}

void Player::setDiscards(const std::vector<Card>* discards) {
    discards_ = discards;
}

const std::vector<Card> * Player::getDiscards() const {
    return discards_;
}

const Hand *Player::getHand() const {
    return hand_;
}

Player::~Player() {
    delete strategy_;
}

Player::Player(const Player& other) : playerNumber_(other.playerNumber_), score_(other.score_),
    hand_(other.hand_), discards_(other.discards_), isHuman_(other.isHuman_) {
    if ( isHuman_ ) {
        strategy_ = new HumanStrategy();
    }
    else {
        strategy_ = new ComputerStrategy();
    }
}

Player& Player::operator= (const Player& other) {
    Player copy{other}; // 2. MyClass copy constructor
    Strategy* temp;

    temp = copy.strategy_; // 3. swap ptr data members
    copy.strategy_ = strategy_;
    strategy_ = temp;
    return *this;
}
