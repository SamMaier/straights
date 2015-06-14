//
// Created by Shiranka Miskin on 6/13/15.
//

#include "table.h"

Table::Table() :  m_cards(new std::set<Card>()) {}
Table::~Table(){ delete m_cards; }

std::set<Card> Table::getCards() const {
    return *m_cards;
}

// 0: Clubs, 1: Diamonds, 2: Hearts, 3: Spades
std::set<Card> Table::getSuit(int suit) const{
    std::set<Card> cards;

    for (const Card & c : *m_cards)
        if (c.getSuit() == suit)
            cards.insert(c);

    return cards;
}

std::ostream &operator<<(std::ostream &out, const Table &t) {

    std::string suits[Suit::SUIT_COUNT] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    for (int suit = 0; suit < Suit::SUIT_COUNT; suit++) {
        out << suits[suit] << ": ";
        std::set<Card> cards = t.getSuit(suit);
        std::set<Card>::iterator it = cards.begin();
        if (it != cards.end()) {
            out << *it;
            it++;
            for (it; it != cards.end(); ++it)
                out << " " << *it;
        }
        if (suit != Suit::SUIT_COUNT - 1)
            out << std::endl;
    }

    return out;

}

void Table::addCard(Card &card) {
    m_cards->insert(card);
}
