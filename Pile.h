#ifndef _PILE_H
#define _PILE_H

#include <vector>
#include <string>
#include "Card.h"

class Pile
{
protected:
	std::vector<Card> pile;

public:
	Pile(){}
	int size() const
	{
		return pile.size();
	}

	virtual void addCard(const Card& c)
	{
		pile.push_back(c);
	}
	virtual bool add(const Card& c)
	{
		pile.push_back(c);
		return true;
	}

	std::string toString() const;  // for saving state
	//toString function should be general so that every pile can
	//implement it

	void readIn(std::istream & is); // students to write this, companion to toString()

	virtual void display() const = 0;  // for live game play, must override

	virtual Card removeCard(int index)
	{
		Card card = pile[index];
		pile.erase(pile.begin()+index);
		return card;
	}

	virtual Card removeCard()
	{
		Card card = pile.back();
		pile.pop_back();
		return card;
	}


};

#endif
