#include <algorithm>
#include <random>
#include "DrawPile.h"

void DrawPile::addDeck(std::vector<Card> & deck)
{
	for(int i = 0; i < (int)deck.size(); i++)
		Pile::pile.push_back(deck[i]);
	deck.clear();
}
void DrawPile::shuffle()
{
	std::vector<Card> draw = Pile::pile;
   	//Shuffles deck, NEED TO KNOW WHAT TYPE IT IS, CANT USE AUTO
   	auto rng = std::default_random_engine{ };
   	std::shuffle(std::begin(draw), std::end(draw), rng);
}
