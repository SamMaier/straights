//
// Created by Shiranka Miskin on 6/13/15.
//

#include "Table.h"

// 0: Clubs, 1: Diamonds, 2: Hearts, 3: Spades
std::set<Card> Table::getSuit(int suit) const{
    std::set<Card> cards;

    for (const Card & c : cards_)
        if (c.getSuit() == suit)
            cards.insert(c);

    return cards;
}

std::ostream &operator<<(std::ostream &out, const Table &t) {

    std::string suits[Suit::SUIT_COUNT] = {"Clubs", "Diamonds", "Hearts", "Spades"};

    for (int suit = 0; suit < Suit::SUIT_COUNT; suit++) {

        out << suits[suit] << ":";

        std::set<Card> cards = t.getSuit(suit);
        std::set<Card>::iterator it = cards.begin();

        // After printing the suit, print only the rank of each following card (The suit is always the last character)
        for (; it != cards.end(); ++it) {
            std::string card = it->toString();
            std::string rank = card.substr(0, card.length() - 1);
            out << " " << rank;
        }
        if (suit != Suit::SUIT_COUNT - 1) // Go to the next line for the next suit if not the last suit
            out << std::endl;
    }

    return out;

}

void Table::playCard(Card card) {
    cards_.insert(card);
}

std::set<Card> Table::getCards() const {
    return cards_;
}
