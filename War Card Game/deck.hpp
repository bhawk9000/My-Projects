// Ben Hawk
// All Rights Reserved

#ifndef DECK_HPP_INCLUDED
#define DECK_HPP_INCLUDED

#include <vector>

#include "player.hpp"
#include "card.hpp"
#include "pile.hpp"

// Don't write a class if you don't have to
using Deck = std::vector<Card>;

Deck make_standard_deck();

Deck Make_combined_deck(const Deck& d1 , const Deck& d2);

void deal(Deck& d, Player& p);

void shuffle(Deck& d);

void print(const Deck& d);

#endif // DECK_HPP_INCLUDED
