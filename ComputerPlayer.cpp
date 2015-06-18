#include "ComputerPlayer.h"
using namespace std;

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber) {};

Command ComputerPlayer::getPlay(const Table& table)  {
    vector<Card> validMoves =  hand_->getValidMoves(table.getCardsOnBoard());

    Command c = Command();

    if ( validMoves.size() > 0){
        c.type = Type::PLAY;
        c.card = validMoves[0];
    }
    else {
        c.type = Type::DISCARD;
        c.card = hand_->getCards()[0];
    }

    return c;

}
