#include <vector>
#include "HumanStrategy.h"
#include "Game.h"
using namespace std;

HumanStrategy::HumanStrategy(View* v) : view_(v){};

Command HumanStrategy::getPlay(const Hand& hand, const Table& table) {
    view_->alertTable(&table);
    view_->alertHand(&hand);

    vector<Card> validMoves =  hand.getValidMoves(table.getCardsOnBoard());
    view_->alertLegalPlays(validMoves);

    Command c = Command();

    do {
        c = view_->getPlay();
    } while (!isValidCommand(c, hand, table));


    return c;

}

bool HumanStrategy::isValidCommand(const Command& c, const Hand& hand, const Table& table) {
    if (c.type == Type::PLAY || c.type == Type::DISCARD) {
        if (Game::isValidPlay(c.card, hand, table)) {
            if (c.type == Type::PLAY) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            if (c.type == Type::PLAY) {
                return false;
            }
            else {
                return true;
            }
        }
    }
    return true;
}
