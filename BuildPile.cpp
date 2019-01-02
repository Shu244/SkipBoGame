#include "BuildPile.h"
/*
 * In SkipBoGame class, when size is 12, the vector of cards is saved.
 * Make sure to have print statement in SkipBoGame when build pile is full.
 * Right when build pile reaches 11, the deck clears.
 */
bool BuildPile::add(const Card& c)
{
	if (c.getValue() == 0)
		Pile::pile.push_back(c);
	else if ((int)Pile::pile.size() + 1 == c.getValue())
		Pile::pile.push_back(c);
	else
		return false;
	return true;
}

