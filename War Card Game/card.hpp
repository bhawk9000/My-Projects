// Ben Hawk
// All Rights Reserved

#ifndef CARD_HPP_INCLUDED
#define CARD_HPP_INCLUDED

#pragma once

#include <utility>
#include <iosfwd>

// Ranks of a c card are:
// ace, 2-10, jack, king, and queen

// suits of a card are:
// hearts, diamonds, clubs, spades

enum Rank // An enumeration type
{
    Ace, // An enumerator
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

// A playing card (in a standard deck) is a pair of rank and suit
class Card
{

private:
    Rank rank;
    Suit suit;


public:

    Card() = default;

    // Construct a card with a rank and suit.
    Card(Rank r, Suit s)
        : rank(r), suit(s) // member initializer list
    {}

    // Copy constructor.
    Card(const Card& c)
        : rank(c.rank), suit(c.suit)
    {}

    // Copy assignment Operator
    Card& operator=(const Card& c)
    {
        rank = c.rank;
        suit = c.suit;
        return *this;
    }

// Accessor and Observer functions

    Rank get_rank() const;
    Suit get_suit() const;

};
bool operator == (Card a, Card b);
bool operator != (Card a, Card b);
bool operator < (Card a, Card b);
bool operator > (Card a, Card b);
bool operator <= (Card a, Card b);
bool operator >= (Card a, Card b);


std::ostream& operator << (std::ostream& os, Card c);
std::ostream& operator << (std::ostream& os, Rank r);
std::ostream& operator << (std::ostream& os, Suit s);

#endif

