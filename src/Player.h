#ifndef _PLAYER_
#define _PLAYER_

#include "Hand.h"
#include "Table.h"
#include "Command.h"
#include "View.h"
#include "Strategy.h"

class View;

class Player {
public:
    Player(int playerNumber, bool isHuman);
    ~Player();
    Player(const Player&);
    Player& operator= (const Player&);
    Command getPlay(const Table&) const;
    std::string getName() const;
    int getNumber() const;
    void ragequit(); // Disable a human player and set it to a computer
    void toggleHuman(); // Toggles between human player to computer player
    void addScore(int score);
    void resetPlayer();
    int getScore() const;
    void setHand(const Hand* hand);
    void setDiscards(const std::vector<Card>* discards);
    bool isHuman() const { return isHuman_; }
    const std::vector<Card>* getDiscards() const;
    const Hand* getHand() const;

private:
    int playerNumber_;
    int score_;
    const Hand* hand_;
    const std::vector<Card>* discards_;
    View* view_;
    bool isHuman_;
    Strategy* strategy_;
};

#endif
