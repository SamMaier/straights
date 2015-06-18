#include <vector>
#include "HumanStrategy.h"
using namespace std;

HumanStrategy::HumanStrategy(View* v) : view_(v){};

Command HumanStrategy::getPlay(const Hand& hand, const Table& table) const{
    vector<Card> validMoves =  hand.getValidMoves(table.getCardsOnBoard());

    Command c = Command();

    if ( validMoves.size() > 0){
        c.type = Type::PLAY;
        c.card = validMoves[0];
    }
    else {
        c.type = Type::DISCARD;
        c.card = hand.getCards()[0];
    }

    return c;

}
