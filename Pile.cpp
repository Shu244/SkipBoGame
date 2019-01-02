#include <iostream>
#include "Pile.h"

// for saving game state - must not change!
std::string Pile::toString() const {
  std::string result;
  result.append(std::to_string(size()));
  result.append("\n");
  // add all the pile elements to the string, at most 20 per line
  for (int i=0; i < size(); ++i) {
    if (i % 20 == 0 && i != 0)
      result.append("\n");
    else if (i != 0)
      result.append(" ");
    result.append(pile[i].toString());
  }
  result.append("\n");
  return result;
}

/*
 * Assuming param is an istream has the following string read
 * #
 * # # # ...
 */
void Pile::readIn(std::istream & is)
{
	std::string num;
	is >> num;
	int num_of_cards = std::stoi(num);
	//std::cout<<num_of_cards<< "         "<<std::endl;
	for(int i = 0; i < num_of_cards; i++)
	{
		is >> num;
		pile.push_back(std::stoi(num));
	}
}
