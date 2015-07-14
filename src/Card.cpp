#include "Card.h"
#include <cassert>
using namespace std;

Card::Card(){
    suit_ = Suit::CLUB;
    rank_ = Rank::ACE;
}

Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}


Suit Card::getSuit() const{
	return suit_;
}

Rank Card::getRank() const{
	return rank_;
}

std::string Card::toString() const{
	string suits[SUIT_COUNT] = {"C", "D", "H", "S"};
	string ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6",
								"7", "8", "9", "10", "J", "Q", "K"};
	return ranks[rank_] + suits[suit_];
}

std::string Card::prettyPrint(std::vector<Card> cards) {
	if (cards.size() <= 0) return "";
	std::string output = "";
	for (unsigned int i = 0; i < cards.size(); i++)
		output += " " + cards[i].toString();
	return output;
}

bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

bool operator!=(const Card &a, const Card &b){
    return !(a == b);
}

bool operator>(const Card &a, const Card &b){
    return a.getSuit() > b.getSuit() || (a.getSuit() == b.getSuit() && a.getRank() > b.getRank());
}

bool operator>=(const Card &a, const Card &b){
    return a > b || a == b;
}

bool operator< (const Card &a, const Card &b){
    return !(a >= b);
}

bool operator<= (const Card &a, const Card &b){
    return !(a > b);
}


ostream &operator<<(ostream &out, const Card &c){
	out << c.toString();
	return out;
}

istream &operator>>(istream &in, Card &c){
	string suits = "CDHS", ranks = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranks.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suits.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
