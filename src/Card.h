#ifndef _CARD_
#define _CARD_

#include <ostream>
#include <istream>
#include <vector>

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
			EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_COUNT };

class Card{
	friend std::istream &operator>>(std::istream &, Card &);

public:
    Card();
	Card(Suit, Rank);
	Suit getSuit() const;
	Rank getRank() const;
	std::string toString() const;
	static std::string prettyPrint(std::vector<Card> cards);

private:
	Suit suit_;
	Rank rank_;
};

bool operator==(const Card &, const Card &);
bool operator!=(const Card &, const Card &);
bool operator< (const Card&, const Card&);
bool operator<= (const Card&, const Card&);
bool operator> (const Card&, const Card&);
bool operator>= (const Card&, const Card&);



//output/input Card in the format <rank><suit>
std::ostream &operator<<(std::ostream &, const Card &);
std::istream &operator>>(std::istream &, Card &);

#endif
