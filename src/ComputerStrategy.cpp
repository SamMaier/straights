#include <vector>
#include "ComputerStrategy.h"
using namespace std;


#define PASSIVE 1


Command ComputerStrategy::getPlay(const Hand& hand, const Table& table) const{

    vector<Card> validMoves =  hand.getValidMoves(table.getCards());

    Command c = Command();

    if ( validMoves.size() > 0){
        c.type = Type::PLAY;
        #if PASSIVE
        c.card = *max_element(validMoves.begin(), validMoves.end());
        #else
        #endif
    }
    else {
        c.type = Type::DISCARD;
        #if PASSIVE
        vector<Card> discardable = hand.getCards();
        c.card = *min_element(discardable.begin(), discardable.end());
        #else
        #endif
    }

    return c;

}
