// Ben Hawk
// All Rights Reserved

#include <iostream>
#include "card.hpp"

Rank Card::get_rank() const
{
    return rank;
}

Suit Card::get_suit() const
{
    return suit;
}

bool operator == (Card a, Card b)
{
    return a.get_rank() == b.get_rank() &&
           a.get_suit() == b.get_suit();
}

bool operator != (Card a, Card b)
{
    return !(a == b);
}

bool operator < (Card a, Card b)
{
    if (a.get_suit() < b.get_suit())
        return true;
    if (b.get_suit() < a.get_suit())
        return false;
    return a.get_rank() < b.get_rank();
}

bool operator > (Card a, Card b)
{
    return b < a;
}

bool operator <= (Card a, Card b)
{
    return !(b < a);
}

bool operator >= (Card a, Card b)
{
    return !(a < b);
}

std::ostream& operator << (std::ostream& os, Rank r)
{
    switch (r)
    {
    case Ace:
        os << 'A';
        break;
    case Two:
        os << '2';
        break;
    case Three:
        os << '3';
        break;
    case Four:
        os << '4';
        break;
    case Five:
        os << '5';
        break;
    case Six:
        os << '6';
        break;
    case Seven:
        os << '7';
        break;
    case Eight:
        os << '8';
        break;
    case Nine:
        os << '9';
        break;
    case Ten:
        os << 'T';
        break;
    case Jack:
        os << 'J';
        break;
    case Queen:
        os << 'Q';
        break;
    case King:
        os << 'K';
        break;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, Suit s)
{
    switch (s)
    {
    case Hearts:
        os << 'H';
        break;
    case Diamonds:
        os << 'D';
        break;
    case Clubs:
        os << 'C';
        break;
    case Spades:
        os << 'S';
        break;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, Card c)
{
    return os << c.get_rank() << c.get_suit();
}
