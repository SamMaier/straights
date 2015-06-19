#include <vector>
#include "HumanStrategy.h"
#include "Game.h"
using namespace std;

HumanStrategy::HumanStrategy(View* v) : view_(v){};


void HumanStrategy::alertPlay(const Hand& hand, const Table& table) const {
    view_->alertTable(&table);
    view_->alertHand(&hand);

    vector<Card> validMoves =  hand.getValidMoves(table.getCardsOnBoard());
    view_->alertLegalPlays(validMoves);
}

Command HumanStrategy::getPlay(const Hand& hand, const Table& table) const{

    vector<Card> validMoves =  hand.getValidMoves(table.getCardsOnBoard());

    Command c = Command();
    bool valid = false;

    do {
        c = view_->getPlay();
        if (c.type == Type::PLAY && !Game::isValidPlay(c.card, hand, table)) {
            view_->alertIllegalPlay();
        } else if(c.type == Type::DISCARD && validMoves.size() > 0) {
            view_->alertNoDiscard();
        } else {
            valid = true;
        }
    } while (!valid);


    return c;

}
