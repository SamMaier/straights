#include <iostream>
#include <vector>
#include "table.h"
#include "deck.h"
#include "hand.h"

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
            table.playCard(c);
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

    static void printHand() {
        Hand hand;
        std::vector<Card> cards;
        cards.push_back(Card(SPADE, EIGHT));
        cards.push_back(Card(SPADE, KING));
        cards.push_back(Card(HEART, EIGHT));
        cards.push_back(Card(SPADE, SEVEN));

        hand.addCard(cards[0]);
        hand.addCard(cards[1]);
        hand.addCard(cards[2]);


        Table table;
        table.playCard(cards[3]);
        std::vector<Card> validMoves = hand.getValidMoves(table.getCardsOnBoard());

        std::cout << "Board:" << std::endl << table << std::endl;
        std::cout << "Your hand: " << hand << std::endl;
        std::cout << "Valid moves: ";
        std::cout << validMoves[0];
        for (unsigned int i = 1; i < validMoves.size(); i++)
            std::cout << " " << validMoves[i];
        std::cout << std::endl;




    }

};
