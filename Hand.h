#include "PlayPile.h"

//five cards are in the hands (could be zero, if it's zero, the display is different: "--")
class Hand : public PlayPile
{
  public:
    Hand() {}

    virtual void display() const;
 
};
