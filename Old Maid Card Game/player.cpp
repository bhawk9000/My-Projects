#include "player.hpp"

void printPlayer(Player p)
{
	for(Player::iterator it = p.begin(); it < p.end(); it++)
	{
		std::cout << *it << " ";
	}

	std::cout << '\n';
}


void removeInitialPairs(Player& p)
{

	while(pairPresent(p))
	{
		removePair(p);
	}

}

void removePair(Player& p)
{
	for(Player::iterator it = p.begin(); it != p.end() - 1; it++)
	{
		if(it->rank == (it + 1)->rank)
		{
			p.erase(it, it + 2); // Erases the matching cards
			break;
		}
	}

}

bool pairPresent(Player& p)
{
	for(Player::iterator it = p.begin(); it != p.end() - 1; it++)
	{
		if(it->rank == (it + 1)->rank)
			return true;
	}

	return false;
}

void addCard(Player& p, Card c)
{
	p.push_back(c);
	std::sort(p.begin(), p.end());
}


void takeCard(Player& p1, Player& p2, int cardIndex)
{
	Card c;

	c = p2[cardIndex];

	p2.erase(p2.begin() + cardIndex);

	addCard(p1, c);
}
