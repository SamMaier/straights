//
// Created by Shiranka Miskin on 6/14/15.
//

#include <unordered_set>
#include "Hand.h"




std::ostream &operator<<(std::ostream &out, const Hand &h) {
    out << Card::prettyPrint(h.getCards());
    return out;
}


std::vector<Card> Hand::getValidMoves(std::set<Card> playedCards) const {
    std::vector<Card> validMoves;

    // If the seven of spades is in a hand, the player must play it
    if ((std::find(cards_.begin(), cards_.end(), Card(SPADE, SEVEN))) != cards_.end() ) {
        validMoves.push_back(Card(SPADE, SEVEN));
        return validMoves;
    }

    // Any card where there is a card on the table of adjacent rank and equal suit is a valid suit
    std::set<Card> allValidMoves;
    for (Card c : playedCards) {
        // Avoid adding a rank above or below the highest or lowest cards respectively
        if (c.getRank() < KING)
            allValidMoves.insert(Card(c.getSuit(), (Rank)(c.getRank() + 1)));
        if (c.getRank() > ACE)
            allValidMoves.insert(Card(c.getSuit(), (Rank)(c.getRank() - 1)));
    }

    // A seven may be played at any point in the game
    for (Card c : cards_) {
        if (allValidMoves.find(c) != allValidMoves.end() || c.getRank() == SEVEN)
            validMoves.push_back(c);
    }

    return validMoves;

}

