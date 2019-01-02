#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include "SkipBoGame.h"

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

bool compareTo(Player p1, Player p2)
{
	return p1.getName() < p2.getName();
}

SkipBoGame::SkipBoGame(string ran, string directory)
{
	string word;
	std::ifstream ifile(directory);
	if (!ifile)
	{
		cout << "invalid program usage: can't open input game file";
		return;
	}
	rand = ran;
	ifile >> word; //Stores previous shuffle condition of draw pile
	ifile >> word; //Stores number of players
	nump = stoi(word);
	//cout << "num players is " << nump << endl;
	ifile >> word; //Stores current player
	curp = stoi(word);

	for (int i = 0; i < nump; i++)
	{
		ifile >> word; //Stores player name
		string name = word;

		ifile >> word; //Stock pile name
		StockPile stock;
		stock.readIn(ifile);

		ifile >> word;
		Hand hand;
		hand.readIn(ifile);

		ifile >> word;
		DiscardPile discard0;
		discard0.readIn(ifile);

		ifile >> word;
		DiscardPile discard1;
		discard1.readIn(ifile);

		ifile >> word;
		DiscardPile discard2;
		discard2.readIn(ifile);

		ifile >> word;
		DiscardPile discard3;
		discard3.readIn(ifile);

		vector<DiscardPile> discard;
		discard.push_back(discard0);
		discard.push_back(discard1);
		discard.push_back(discard2);
		discard.push_back(discard3);

		Player p(name, stock, hand, discard);
		peep.push_back(p);
	}

	//Sorts players by name.
	sort(peep.begin(), peep.end(), compareTo);

	ifile >> word;
	DrawPile draw;
	draw.readIn(ifile);

	drawpile = draw;
	if (rand=="true")
		draw.shuffle();


	ifile >> word;
	BuildPile ba;
	ba.readIn(ifile);

	ifile >> word;
	BuildPile bb;
	bb.readIn(ifile);

	ifile >> word;
	BuildPile bc;
	bc.readIn(ifile);

	ifile >> word;
	BuildPile bd;
	bd.readIn(ifile);

	vector<BuildPile> b;
	b.push_back(ba);
	b.push_back(bb);
	b.push_back(bc);
	b.push_back(bd);

	build = b;

	//Dont forget to shuffle draw pile

	for (int i = 0; i < getNumPlayers(); i++)
	{
		peep[i].setBuild(&build);
		peep[i].setDraw(&drawpile);
	}
}

SkipBoGame::SkipBoGame(int num_player, int num_stock, vector<Card> deck,
					   string rand) : nump(num_player), curp(0), rand(rand)
{
	drawpile.setDeck(deck);
	if (rand == "true")
	{
		drawpile.shuffle();
		curp = (std::rand() % nump);
	}

	for (int i = 0; i < 4; i++)
		build.push_back(BuildPile());

	for (int i = 0; i < num_player; i++)
	{
		std::stringstream name;
		name << "Player" << i;
		string player_name = name.str();
		Player p(player_name, &build, &drawpile);
		peep.push_back(p);
	}
	//What happens when there arn't enough cards.
	for (int i = 0; i < num_stock; i++)
	{
		for (int j = 0; j < num_player; j++)
		{
			peep[j].addStock();
		}
	}
}

/* for live game play - must not change format!

 drawPile  build_a  build_b  build_c  build_d
 playerName  stock_0
 discards: discard_1 discard_2 discard_3 discard_4
 hand: card_5 card_6 card_7 card_8 card_9
 */
void SkipBoGame::display() const
{
	//cout<<"In display() function" << endl;
	std::cout << "Draw: ";
	drawpile.display();
	std::cout << " Build Piles: ";
	for (int j = 0; j < 4; j++)
	{
		//cout<<"Displaying build pile" << endl;
		build[j].display();
		std::cout << " ";
	}
	std::cout << std::endl;
	peep[curp].display();
}

/* for saving state - must not change format!

 shuffle numplayers currplayer
 PlayerCurp [display]
 PlayerCurp+1 [display]
 [etc for all players]
 Draw [display]
 Build_a [display]
 Build_b [display]
 Build_c [display]
 Build_d [display]
 */
std::string SkipBoGame::toString() const
{
	std::stringstream result;
	int idx;
	result << rand << " " << nump << " " << curp << "\n";
	for (int i = 0; i < nump; ++i)
	{
		idx = (curp + i) % nump;
		result << peep[idx].toString();
	}
	result << "Draw " << drawpile.toString();
	for (int j = 0; j < 4; j++)
	{
		result << "Build_" << char('a' + j) << " ";
		result << build[j].toString();
	}
	return result.str();
}

//return false if the player's turn has ended
/*
 * First return is false if player's turn has ended
 * Second return is true if player won.
 */
pair<bool, bool> SkipBoGame::turn(int curp)
{
	//cout << "In turn() function" << endl;
	display();
	cout << "(m)ove [start] [end] or (d)raw ? ";
	string command;
	getline(cin, command);
	bool continuePlaying;

	pair<bool, bool> results = peep[curp].makePlay(command);

	//first is true if the move was legal
	if (!results.first)
	{
		cout << "illegal command, try again" << endl;
		return make_pair(true, false);
	}
	//Second is true if player moved card to discard.
	else if (results.second)
		continuePlaying = false;
	else
		continuePlaying = true;

	return make_pair(continuePlaying, peep[curp].won());
}

void SkipBoGame::playGame(vector<Card> aside)
{
	displayP();
	string user_input, dummy;
	cin >> user_input;

	getline(cin, dummy); //To read newline from asking if the player wants to save, quit, or play.
	//cout << dummy << endl;

	if (user_input == "q")
		cout << "thanks for playing" << endl;
	else if (user_input == "s")
	{
		cout << "save filename: ";
		cin >>user_input;
		if (aside.size() != 0)
			drawpile.addDeck(aside);
		saveGame(user_input);
	}
	else if (user_input == "p")
	{
		peep[curp].drawCards();
		pair<bool, bool> oneTurn;
		bool prt = true;
		do
		{
			oneTurn = turn(curp);

			for (int i = 0; i <= 3; i++)
			{
				if (build[i].size() == 12)
				{
					prt = false;
				}
			}
			if(prt)
			cout << endl;
			if (oneTurn.second)
			{
				gameOver();
				return;
			}
			for (int i = 0; i <= 3; i++)
			{
				if (build[i].size() == 12)
				{
					char name = 'a' + i;
					cout << "build pile " << name << " full, set aside" << endl;
					vector<Card> removed = build[i].clearCards();
					for (int i = 0; i < (int)removed.size(); i++)
						aside.push_back(removed[i]);
				}
			}
			if(!prt)
			cout << endl;
			if (drawpile.size() == 0)
				drawpile.addDeck(aside);
		} while (oneTurn.first);
		display();
		cout << endl;
		curp = (curp + 1) % nump;
		playGame(aside);
	}
	else
	{
		cout << "illegal command, try again" << endl;
		playGame(aside);
	}
}
//For displaying the first two lines for each player
void SkipBoGame::displayP()
{
	cout << " >> " << peep[curp].getName() << " turn next" << endl;
	cout << "(p)lay, (s)ave, or (q)uit ? ";
}
void SkipBoGame::saveGame(string ofile)
{
	std::ofstream savefile(ofile);
	if (!savefile)
	{
		cout << "fail to open output file";
	}
	savefile << toString();
}
