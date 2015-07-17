#include <vector>
#include "ComputerStrategy.h"
using namespace std;


/* The algorithm that the Computer player uses is this:
 *
 * Let a "block" refer to a sequence of consecutive cards of a suit
 *
 * If valid plays exist:
 *    We want to play a high value card so that it won't need to be discarded,
 *    however if a block of cards has a playable card, all of its cards in the block,
 *    are playable regardless of what state of the board we get to in the future.
 *    This means we gain more by holding on to the cards as it will reduce the
 *    possible plays opponents can make.  Therefore our algorithm for making a play
 *    is to play the highest card which is not in our highest block of a suit.
 *
 * If no plays exist:
 *    By discarding cards between 8 and 10 inclusive, we force discards of at least
 *    a Jack, Queen, and King.  This results in a net loss of at least 36 points while
 *    we lose only at most 10 points, therefore it is good to discard these cards.
 *    If these plays are not possible, we simply discard the lowest card in our hand
 *    to minimize points.
 */

Command ComputerStrategy::getPlay(const Hand& hand, const Table& table) const{
    Command c = Command();

    vector<Card> validMoves =  hand.getValidMoves(table.getCards());
    vector<Card> cardsInHand = hand.getCards();


    // Sort the lists from lowest points to highest points
    sort(validMoves.begin(), validMoves.end());
    sort(cardsInHand.begin(), cardsInHand.end());

    // Determine the starting point of the highest blocks of cards for each suit
    vector<Card> cardsOfSuit[SUIT_COUNT];
    Card highestBlocks[SUIT_COUNT];

    // Create lists for each suit of cards
    for (Card c : cardsInHand)
        cardsOfSuit[c.getSuit()].push_back(c);

    // Determine the lowest card of the highest block of each suit
    for (int suit = 0; suit < SUIT_COUNT; suit++) {
        vector<Card> cards = cardsOfSuit[suit];
        if (cards.empty()) continue;

        int highestBlockStart = cards.size() - 1;
        while (highestBlockStart > 0 && cards[highestBlockStart - 1].getRank() == cards[highestBlockStart].getRank() - 1) {
            highestBlockStart--;
        }
        highestBlocks[suit] = cards[highestBlockStart];
    }

    if (validMoves.size() > 0){
        // If we must play, play the highest card which is not within the highest block of cards in its suit
        c.type = Type::PLAY;
        int cardToPlay = validMoves.size() - 1;
        Card candidate = validMoves[cardToPlay];
        while (cardToPlay != 0 && candidate >= highestBlocks[candidate.getSuit()]) {
            cardToPlay--;
            candidate = validMoves[cardToPlay];
        }
        c.card = candidate;

    } else {
        c.type = Type::DISCARD;
        // If we must discard, discard the highest card between 10 and 7 which is within the highest block
        int cardToDiscard = cardsInHand.size() - 1;
        Card candidate = cardsInHand[cardToDiscard];
        while (cardToDiscard != 0 && (candidate.getRank() > Rank::TEN || candidate < highestBlocks[candidate.getSuit()])) {
            cardToDiscard--;
            Card next = cardsInHand[cardToDiscard];
            if (next.getRank() <= Rank::SEVEN)
                break;
            else
                candidate = next;
        }
        if (candidate.getRank() > Rank::SEVEN && candidate.getRank() <= Rank::TEN)
            c.card = candidate;
        else
            c.card = cardsInHand[0];
    }


    return c;

}
