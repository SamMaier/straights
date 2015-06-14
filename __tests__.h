#include <iostream>
#include <vector>
#include "table.h"
#include "deck.h"

class Test {
public:
    static void printTable() {
        std::vector<Card> cards;
        cards.push_back(Card(CLUB, EIGHT));
        cards.push_back(Card(SPADE, KING));
        cards.push_back(Card(SPADE, SEVEN));
        cards.push_back(Card(SPADE, FIVE));
        cards.push_back(Card((Suit)2, (Rank)3)); // 4 of hearts

        for (int rank = RANK_COUNT - 1; rank >= 0; rank--) {
            cards.push_back(Card(Suit::DIAMOND, (Rank) rank));
        }

        Table table;
        for (Card & c : cards) {
            table.addCard(c);
        }

        std::cout << table << std::endl;
        std::cout << SUIT_COUNT * RANK_COUNT << std::endl;
    }

    static void printDeck() {
        Deck deck;
        std::cout << deck << std::endl;
        std::cout << std::endl;
        deck.shuffle();
        std::cout << deck << std::endl;
    }
};
