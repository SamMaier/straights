//
// Created by Shiranka Miskin on 6/14/15.
//

#include <unordered_set>
#include "Hand.h"




std::ostream &operator<<(std::ostream &out, const Hand &h) {
    std::vector<Card> cards = h.getCards();
    if (cards.size() <= 0) return out;
    out << cards[0];
    for (int i = 1; i < cards.size(); i++)
        out << " " << cards[i];
    return out;
}


std::vector<Card> Hand::getValidMoves(std::set<Card> playedCards) const {
    std::vector<Card> validMoves;

    // If the seven of spades is in a hand, the player must play it
    if ((std::find(cards_.begin(), cards_.end(), Card(SPADE, SEVEN))) != cards_.end() ) {
        validMoves.push_back(Card(SPADE, SEVEN));
        return validMoves;
    }

    std::set<Card> allValidMoves;
    for (Card c : playedCards) {
        if (c.getRank() < KING)
            allValidMoves.insert(Card(c.getSuit(), (Rank)(c.getRank() + 1)));
        if (c.getRank() > ACE)
            allValidMoves.insert(Card(c.getSuit(), (Rank)(c.getRank() - 1)));
    }
    for (Card c : cards_) {
        if (allValidMoves.find(c) != allValidMoves.end() || c.getRank() == SEVEN)
            validMoves.push_back(c);
    }

    return validMoves;

}

