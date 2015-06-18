//
// Created by Shiranka Miskin on 6/17/15.
//

#include <iostream>
#include "TextView.h"

void TextView::alertPlayedCard(Player *player, Card card) {
    std::cout << "Player " << player->getName() << " plays " << card << "." << std::endl;
}

void TextView::alertDiscardCard(Player *player, Card card) {
    std::cout << "Player " << player->getName() << " discards " << card << "." << std::endl;
}

void TextView::alertRagequit(Player* player) {
    std::cout << "Player " << player->getName() << " ragequits.  A computer will now take over." << std::endl;
}

void TextView::alertGameEnd(Player* winner) {
    std::cout << "Player " << winner->getName() << " wins!" << std::endl;
}

void TextView::alertBeginRound(Player *firstPlayer) {
    std::cout << "A new round begins.  It's player " << firstPlayer->getName() << "'s turn to play." << std::endl;
}

void TextView::alertEmptyHand(Player *player, int oldScore) {
    int scoreGained = player->getScore() - oldScore;
    std::cout << "Player " << player->getName() << "'s discards: " << Card::prettyPrint(*(player->getDiscards())) << std::endl;
    std::cout << "Player " << player->getName() << "'s score: " << oldScore << " + " << scoreGained << " = " << player->getScore() << std::endl;

}

void TextView::alertDeck(Deck* deck) {
    std::cout << *deck << std::endl;
}

void TextView::alertTable(Table *table) {
    std::cout << "Cards on the table:" << std::endl;
    std::cout << *table << std::endl;
}

bool TextView::checkIfHuman(std::string playerName) {
    std::cout << "Is player " << playerName << " a human(h) or a computer(c)?" << std::endl;
    std::string input;
    std::cout << ">";
    std::cin >> input;
    return input == "h";
}

Command TextView::getPlay() {
    Command command;
    std::cout << ">";
    std::cin >> command;
    return command;
}

void TextView::alertHand(Hand *hand) {
    std::cout << "Your hand: " << *hand << std::endl;
}

void TextView::alertLegalPlays(std::vector<Card> legalPlays) {
    std::cout << "Legal plays: " << Card::prettyPrint(legalPlays) << std::endl;
}

void TextView::alertIllegalPlay() {
    std::cout << "This is not a legal play." << std::endl;
}

void TextView::alertNoDiscard() {
    std::cout << "You have a legal play.  You may not discard." << std::endl;
}

