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

void GameController::disablePlayer() {
    game_->disablePlayer();
}

void GameController::exit() {
    game_->running_ = false;
}
