//
// Created by Shiranka Miskin on 6/27/15.
//

#include "GameController.h"

GameController::GameController(Game *game): game_(game) {
}

void GameController::play(Card card) {
    game_->play(card);
    game_->nextTurn();
}

void GameController::discard(Card card) {
    game_->discard(card);
    game_->nextTurn();
}

void GameController::toggleHuman(int playerNumber) {
    game_->toggleHuman(playerNumber);
}

void GameController::startNextRound() {
    game_->startNextRound();
}

void GameController::exit() {
    game_->running_ = false;
}

void GameController::endGame() {
    game_->endGame();
}

void GameController::startGame(int seed) {
    game_->startGame(seed);
}
