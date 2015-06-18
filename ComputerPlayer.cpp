#include "ComputerPlayer.h"
#include "Command.h"
#include "Card.h"
using namespace std;

ComputerPlayer::ComputerPlayer(int playerNumber) : Player(playerNumber) {};

Command ComputerPlayer::getPlay(const Table& table) const {
    vector<Card> validMoves =  hand_->getValidMoves(table.getCardsOnBoard());

    if ( validMoves.size() > 0){

    }
    else {
        Command c = Command();

    }

}
