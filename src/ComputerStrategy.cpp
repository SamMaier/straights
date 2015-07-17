#include <vector>
#include "ComputerStrategy.h"
using namespace std;


Command ComputerStrategy::getPlay(const Hand& hand, const Table& table) const{

    vector<Card> validMoves =  hand.getValidMoves(table.getCards());

    Command c = Command();

    if ( validMoves.size() > 0){
        c.type = Type::PLAY;
        c.card = *max_element(validMoves.begin(), validMoves.end());
    }
    else {
        c.type = Type::DISCARD;
        vector<Card> discardable = hand.getCards();
        c.card = *min_element(discardable.begin(), discardable.end());
    }

    return c;

}
