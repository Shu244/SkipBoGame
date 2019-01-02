#ifndef _BUILDPILE_H
#define _BUILDPILE_H

#include "PlayPile.h"
//for each game, four buildpile objects are created
class BuildPile : public FaceUpPile
{
  public:
    BuildPile() { }

     virtual bool add(const Card &c);
     std::vector<Card> clearCards()
     {
    	 std::vector<Card> removed = Pile::pile;
    	 Pile::pile.clear();
    	 return removed;
     }
};

#endif
