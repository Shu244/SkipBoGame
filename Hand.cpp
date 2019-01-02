#include "Hand.h"
#include <iostream>

/*************************************
 For SkipBo - Fall 2018 - EN.601.220
 Instructor provided code
 *************************************/

/*
 *In SkipBoGame class, need to handle when to redraw 5 cards
 *Make sure to print new line in SkipBoGame
 */
void Hand::display() const
{
	int count = 5;
	for (int i = 0; i < Pile::size(); i++)
	{
		Pile::pile[i].display();
		std::cout<<"  ";
		count--;
	}
	for (int i = 0; i < count; i++)
		std::cout << "--  ";
}



