#include "deck.hpp"

#include <iostream>
#include <random>
#include <algorithm>

Deck makeStandardDeck()
{
    Deck d
    {
        {Ace, Spades},
        {Two, Spades},
        {Three, Spades},
        {Four, Spades},
        {Five, Spades},
        {Six, Spades},
        {Seven, Spades},
        {Eight, Spades},
        {Nine, Spades},
        {Ten, Spades},
        {Jack, Spades},
        {Queen, Spades},
        {King, Spades},

        {Ace, Clubs},
        {Two, Clubs},
        {Three, Clubs},
        {Four, Clubs},
        {Five, Clubs},
        {Six, Clubs},
        {Seven, Clubs},
        {Eight, Clubs},
        {Nine, Clubs},
        {Ten, Clubs},
        {Jack, Clubs},
        {Queen, Clubs},
        {King, Clubs},

        {Ace, Hearts},
        {Two, Hearts},
        {Three, Hearts},
        {Four, Hearts},
        {Five, Hearts},
        {Six, Hearts},
        {Seven, Hearts},
        {Eight, Hearts},
        {Nine, Hearts},
        {Ten, Hearts},
        {Jack, Hearts},
        {Queen, Hearts},
        {King, Hearts},

        {Ace, Diamonds},
        {Two, Diamonds},
        {Three, Diamonds},
        {Four, Diamonds},
        {Five, Diamonds},
        {Six, Diamonds},
        {Seven, Diamonds},
        {Eight, Diamonds},
        {Nine, Diamonds},
        {Ten, Diamonds},
        {Jack, Diamonds},
        //{Queen, Diamonds},
        {King, Diamonds},
    };

    return d;
}

Deck makeCombinedDeck(const Deck& d1, const Deck& d2)
{
    Deck d;

    d.insert(d.end(), d1.begin(), d1.end());
    d.insert(d.end(), d2.begin(), d2.end());

    return d;
}

void shuffleDeck(Deck& d)
{
    extern std::minstd_rand prng;

    std::shuffle(d.begin(), d.end(), prng);
}

void printDeck(const Deck& d)
{
    int i = 1;

    for (Card c : d)
    {
        std::cout << c << ' ';
        if (i % 13 == 0)
        {
            std::cout << '\n';
            i = 0;
        }
        ++i;
    }

    std::cout << '\n';
}
