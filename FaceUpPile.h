#ifndef _FACEUPPILE_H
#define _FACEUPPILE_H

#include "Pile.h"

class FaceUpPile: public Pile
{
public:
	FaceUpPile()
	{
	}

	virtual Card get(int index) const
	{
		return pile[index];
	}
	virtual Card get() const
	{
		return pile.back();
	}
	virtual void display() const;

};

#endif
