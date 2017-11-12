#include "card.hpp"
#include "deck.hpp"
#include "player.hpp"

#include <iostream>
#include <algorithm>
#include <deque>
#include <string>
#include <random>

int randomIndex(int upperBound);
void printQueue(std::deque<Player> q, int numPlayers);
void dealDeck(Deck& deck, std::vector<Player>& players);

std::random_device rng;
std::minstd_rand prng;


int main()
{
    int numPlayers = 4;
    Player pCopy;

    Deck deck {makeStandardDeck()};
    std::vector<Player> players(numPlayers);

    prng.seed(rng());

    shuffleDeck(deck);
    dealDeck(deck, players);

    std::deque<Player> gameQueue;
    for(std::vector<Player>::iterator it = players.begin(); it != players.end(); it++)
    {
        removeInitialPairs(*it);
        gameQueue.push_back(*it);
    }


    while(gameQueue.size() > 1)
    {
        pCopy = gameQueue.front();
        gameQueue.pop_front();

        int index = randomIndex(gameQueue.back().size());
        takeCard(pCopy, gameQueue.back(), index);

        if(gameQueue.back().size() == 0)
            gameQueue.pop_back();

        removePair(pCopy);

        if(pCopy.size() > 0)
            gameQueue.push_back(pCopy);
    }

    return 0;
}


int randomIndex(int upperBound)
{
    std::uniform_int_distribution<> d(0, upperBound - 1);

    return d(prng);
}

void dealDeck(Deck& deck, std::vector<Player>& players)
{
    //Iterator to navigate player hands (initialized to the first player)
    std::vector<Player>::iterator pit {players.begin()};

    // Loops through deck, handing out a card to one of n unique players each iteration
    for(Deck::iterator dit = deck.begin(); dit != deck.end(); dit++)
    {
        addCard(*pit, *dit); // *pit == a player, *dit == a card
        pit++; // Increments pit to the next player


        if(pit == players.end())
            pit = players.begin();
    }
}
