#include <iostream>
#include "table.h"

class Test {
public:
    static void printTable() {
        Table table;
        Card card(Suit::CLUB, Rank::EIGHT);
        Card card2(Suit::SPADE, Rank::KING);
        Card card3(Suit::SPADE, Rank::SEVEN);
        table.addCard(card);
        table.addCard(card2);
        table.addCard(card3);

        std::cout << table << std::endl;
    }
};
