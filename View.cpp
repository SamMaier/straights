//
// Created by Shiranka Miskin on 6/17/15.
//

#include "View.h"

void View::alertPlayedCard(Player *player, Card card) {
}

void View::alertDiscardCard(Player *player, Card card) {
}

void View::alertRagequit(Player *player) {
}

void View::alertGameEnd(Player *winner) {
}

void View::alertBeginRound(Player *firstPlayer) {
}

void View::alertEmptyHand(Player *player, int oldScore) {
}

void View::alertDeck(Deck *deck) {
}

bool View::checkIfHuman(std::string playerName) {
    return false;
}

void View::alertTable(Table *table) {
}

void View::alertHand(Hand *hand) {
}

void View::alertLegalPlays(std::vector<Card> legalPlays) {
}

void View::alertIllegalPlay() {
}

void View::alertNoDiscard() {
}

Command View::getPlay() {
}
