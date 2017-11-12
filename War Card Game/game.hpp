// Ben Hawk
// All Rights Reserved

#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "deck.hpp"

#pragma once

struct Options
{
    int num_decks = 1;
    bool ace_high = true;
    int num_sacrafice = 1;
    bool negotiable_sacrafice = true;
};

struct Game
{
    Deck deck;
    Player p1;
    Player p2;
    Pile pile;
    int turn;

};

#endif // GAME_HPP_INCLUDED
