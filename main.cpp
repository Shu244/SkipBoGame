//Determine whether all includes are necessary
#include <iostream>
#include <vector>
#include <fstream>
#include "SkipBoGame.h"
#include <stdio.h>
#include <string>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
	//Starting a new game
	if (argc == 5)
	{
		if (std::strcmp(argv[1], "true") != 0 && std::strcmp(argv[1], "false") != 0)
		{
			cout << "invalid program usage: invalid first argument" << endl;
			return 1;
		}
		//start to read in the deck:
		std::ifstream ifile(argv[4]);
		int num_player = atoi(argv[2]);
		int num_stock = atoi(argv[3]);
		if (!ifile)
		{
			cout << "num players is " << num_player << endl;
			cout << "stock size is " << num_stock << endl;
			cout << "invalid program usage: can't open deck file" << endl;
			return 1;
		}
		int card_value;
		std::vector<Card> draw;
		while (ifile >> card_value) //What if card_value is less than 162, the expected number of cards?
			draw.push_back(Card(card_value));

		string shuffle = argv[1]; //if true, then random player starts and draw pile is shuffled.

		//Creates drawpile,name players, gives them access to build and draw piles, deals stock cards to them.
		SkipBoGame game(num_player, num_stock, draw, shuffle);

		//ready to start the game now: start from curp
		if (num_player < 2 || num_player > 6)
		{
			cout << "invalid program usage: num players must be 2-6" << endl;
			return 1;
		}
		cout << "num players is " << num_player << endl;
		if (num_player * num_stock > (int)draw.size())
		{
			cout << "invalid program usage: bad stock size" << endl;
			return 1;
		}
		if ((num_player > 4 && num_player <= 6) && num_stock > 20)
		{
			cout << "invalid program usage: bad stock size" << endl;
			return 1;
		}
		if (num_stock < 1 || num_stock > 30)
		{
			cout << "invalid program usage: bad stock size" << endl;
			return 1;
		}
		cout << "stock size is " << num_stock << endl
			 << endl;
		std::vector<Card> aside;
		game.playGame(aside);
	}
	else if (argc == 3) //open from a saved game
	{
		std::ifstream ifile(argv[2]);
		if (std::strcmp(argv[1], "true") != 0 && std::strcmp(argv[1], "false") != 0)
		{
			cout << "invalid program usage: invalid first argument" << endl;
			return 1;
		}
		if (!ifile)
		{
			cout << "invalid program usage: can't open input game file" << endl;
			return 1;
		}
		SkipBoGame game(argv[1], argv[2]);
		if (game.getNumPlayers() < 2 || game.getNumPlayers() > 6)
		{
			cout << "invalid program usage: num players must be 2-6" << endl;
			return 1;
		}
		//ready to start the game now: start from curp
		cout << endl;
		std::vector<Card> aside;
		game.playGame(aside);
	}
	else
	{
		cout << "invalid program usage: invalid number of arguments" << endl;
		return 1;
	}
	return 0;
}
