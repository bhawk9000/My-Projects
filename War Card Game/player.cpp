// Ben Hawk
// All Rights Reserved

#include "player.hpp"

void give(Player& player, Pile& pile)
{
    while (!pile.empty())
    {
        player.push_back(pile.back());
        pile.pop_back();
    }
}

Card take(Player& player)
{
    Card c = player.front();
    player.erase(player.begin());
    return c;
}
