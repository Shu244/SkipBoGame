#ifndef _DRAWPILE_H
#define _DRAWPILE_H

#include "Pile.h"
#include <iostream>

class DrawPile : public Pile {
    public:
    DrawPile(){}

    virtual void setDeck(const std::vector<Card> & deck)
    {
    	Pile::pile = deck;
    }
    virtual void addDeck(std::vector<Card> & deck);
    void shuffle();
    virtual void display() const
    {
        std::cout << "[XX]/" <<  Pile::size() << " ";
    }
    /*
     * returns the card at the back of the deck
     */
};
#endif
