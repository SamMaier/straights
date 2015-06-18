#include <vector>
#include "ComputerStrategy.h"
using namespace std;

Command ComputerStrategy::getPlay(const Hand& hand, const Table& table) const{
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
