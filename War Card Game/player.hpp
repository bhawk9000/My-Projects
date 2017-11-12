// Ben Hawk
// All Rights Reserved

#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include "pile.hpp"
#include "card.hpp"

using Player = std::vector<Card>;

void give(Player& p, Pile& s);

Card take(Player& p);

#endif // PLAYER_HPP_INCLUDED
