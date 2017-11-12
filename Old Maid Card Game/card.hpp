#ifndef CARD_HPP_INCLUDED
#define CARD_HPP_INCLUDED

#include <iosfwd>

enum Rank
{
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
};

enum Suit
{
	Hearts,
	Diamonds,
	Clubs,
	Spades,
};

class Card
{
public:
	Card() = default;

	Card(Rank r, Suit s)
		: rank(r), suit(s)
	{}

	Rank rank;
	Suit suit;
};

bool operator==(Card a, Card b);
bool operator!=(Card a, Card b);

bool operator<(Card a, Card b);
bool operator>(Card a, Card b);
bool operator<=(Card a, Card b);
bool operator>=(Card a, Card b);

std::ostream& operator<<(std::ostream& os, Card c);
std::ostream& operator<<(std::ostream& os, Suit s);
std::ostream& operator<<(std::ostream& os, Rank r);

#endif // CARD_HPP_INCLUDED
