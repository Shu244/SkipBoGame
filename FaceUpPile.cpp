#include "FaceUpPile.h"
#include <iostream>


void FaceUpPile::display() const
{
	//std::cout<<"In FaceUpPile display()"<<std::endl;
	if(Pile::pile.size() == 0)
		std::cout << "--";
	else
		Pile::pile.back().display();
	std::cout << "/" << Pile::pile.size();
}

