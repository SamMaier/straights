#include "HumanPlayer.h"
using namespace std;

HumanPlayer::HumanPlayer(int playerNumber) : Player(playerNumber) {};

Command HumanPlayer::getPlay(const Table& table)  {
    vector<Card> validMoves =  hand_->getValidMoves(table.getCardsOnBoard());

     return Command();

}
