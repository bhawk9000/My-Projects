// Ben Hawk
// All Rights Reserved

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <cassert>

#include "card.hpp"
#include "deck.hpp"

std::random_device rng;//makes it impossible to guess the random number generator
std::minstd_rand prng;

// Deck of cards
// - which cards/ SUITED, jokers?
// - how many cards? how many decks?
// - ???

// Players
// - How many players? usually 2.
// - no strategy
// - per player acquisin strategy...
// - names?
// - hand (stack/queue of cards)

// Spoils pile
// - determines how cards are picked up?

// Game options
// - deck specifications/size
// - aces low or high
// - acquisition rules (SPOILs)
//   - winer's first
//   - loser's first
//   - sorted (asending/descending)
//   - shuffled
//   - partially shuffled (per war)
//   - interspersed per war
// - number of sacrifices (1, 3, more?)
// - negotiable sacrifice ( possibly 0)
// - incremental sacrifice
//   - global or local counter?

int main()
{
    prng.seed(rng());

    double runs = 100;
    int total = 0;

    Deck deck = make_standard_deck();
    shuffle(deck);

    Player p1;
    Player p2;

    // Round-robin dealing.
    while (!deck.empty())
    {
        deal(deck, p1);
        deal(deck, p2);
    }

    // The spoils pile.
    Pile spoils;

    print(p1);
    print(p2);

    for (int i = 0; i < runs; ++i)
    {
        if (p1.empty())
        {
            if (p2.empty())
            {
                std::cout << "TIE\n";
                total += i;
            }
            else
            {
                std::cout << "P2 WINS\n";
                total += i;
                break;
            }

        }
        else if (p2.empty())
        {
            std::cout << "P1 WINS\n";
            total += i;
            break;
        }

        Card c1 = take(p1);
        Card c2 = take(p2);

        spoils.push_back(c1);
        spoils.push_back(c2);

        print(spoils);
        std::cout << std::endl;
        print(p1);
        std::cout << std::endl;
        print(p2);
        std::cout << std::endl;
        std::cout << c1 << " " << c2 << std::endl;

        if (c1 > c2)
        {
            give(p1, spoils);
            total += i;
        }
        else if (c2 > c1)
        {
            give(p2, spoils);
            total += i;
        }
        else
        {
            std::cout << "There are " << spoils.size() << " cards in the spoils pile" << std::endl;

            // WAR!
            spoils.push_back(take(p1));
            spoils.push_back(take(p2));
            total += i;
            continue;
        }
        assert(spoils.empty());
    }
    std::cout << "The average number of turns in a game of war is " <<
              (total / runs) << " turns." << std::endl;
    return 0;
}
