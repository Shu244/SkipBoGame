#include <iostream>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <cstdbool>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include "Player.h"

using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;

// for live game play - must not change!
void Player::display() const
{
	std::cout << "Current ";
	std::cout << name << ":  Stock{0}: ";
	stock.display();
	std::cout << std::endl;
	std::cout << "   Discards{1-4}: ";
	for (int i = 0; i < 4; ++i)
	{
		discard[i].display();
		std::cout << "  ";
	}
	std::cout << std::endl;
	std::cout << "   Hand{5-9}: ";
	hand.display();
	std::cout << std::endl;
}

/* saving state format - must not change!
 PlayerName
 Stock size
 01 02 03  ...
 ...
 Hand size
 01 02 03 04 05
 Discard1 size
 01 02 03 04 ...
 ...
 Discard2 size
 ...
 Discard3 size
 ...
 Discard4 size
 ...
 */
std::string Player::toString() const
{
	std::stringstream result;
	result << name << "\n";
	result << "Stock " << stock.toString();
	result << "Hand " << hand.toString();
	for (int i = 0; i < 4; ++i)
	{
		result << "Discard" << i << " " << discard[i].toString();
	}
	return result.str();
}

/*
 * command will be in the form of c #(0-9) c(a-d)/#(1-4)
 * Returns true if makeMove occured successfully.
 * first bool is whether card was added and second bool is whether added card is discard card.
 */
pair<bool, bool> Player::makePlay(string command) //first bool check if makeplay sucessful, the second check if turn is ended
{
	std::stringstream in(command);
	string word;
	in >> word;

	if (word == "d")
	{
		if (hand.size() != 0)
			return make_pair(false, false);
		else
			drawCards();
		return make_pair(true, false);
	}
	else if (word == "m")
	{
		try
		{
			in >> word;
			if (word.length() > 1)
				return make_pair(false, false);
			int start = (int)word[0]-48;

			in >> word;
			if (word.length() > 1)
				return make_pair(false, false);
			char end = word[0];
			bool endgame = false;
			if (isdigit(end) && end >= '1' && end <= '4')
				endgame = true;
			return make_pair(move(start, end), endgame);
		}
		catch (std::exception &e)
		{
			return make_pair(false, false);
		}
	}
	else
		return make_pair(false, false);
}

void Player::drawCards()
{
	int size = hand.size();
	for (int i = 0; i < 5 - size; i++)
		hand.addCard(draw->removeCard());
}
bool Player::legalMove(Card toMove, Pile &start, int index, Pile * end)
{
	if (end->add(toMove))
	{
		start.removeCard(index);
		return true;
	}
	return false;
}
//buildpiles are labelled a-d while stock, hand, discard are from 0-9
bool Player::move(int start, char end)
{
	if ((start > 0) && (start < 5)) //check if trying to take card from discard which is empty
	{
		if (discard[start-1].size() == 0)
			return false;
	}
	if (!(start >= 0 && start <= 9))
		return false;
	
	FaceUpPile * moveTo;

	if (isdigit(end) && end >= '1' && end <= '4')
	{
		end = end - 1;
		switch (end)
		{
		case '0':
			moveTo = &discard[0];
			break;
		case '1':
			moveTo = &discard[1];
			break;
		case '2':
			moveTo = &discard[2];
			break;
		case '3':
			moveTo = &discard[3];
			break;
		}
	}
	else if (isalpha(end) && end >= 'a' && end <= 'd')
	{
		std::vector<BuildPile> &bd = *(this->build);
		switch (end)
		{
		case 'a':
			moveTo = &bd[0];
			break;
		case 'b':
			moveTo = &bd[1];
			break;
		case 'c':
			moveTo = &bd[2];
			break;
		case 'd':
			moveTo = &bd[3];
			break;
		}
	}
	else
		return false;

	switch (start)
	{

	//arguments of legalMove(Card being moved, Pile where card is being moved,
	//index of card being moved, Pile where card is being moved to)
	case 0:
		return legalMove(stock.get(), stock, stock.size()-1, moveTo);
	case 1:
		return legalMove(discard[0].get(), discard[0], discard[0].size()-1,
						 moveTo);
	case 2:
		return legalMove(discard[1].get(), discard[1], discard[1].size()-1,
						 moveTo);
	case 3:
		return legalMove(discard[2].get(), discard[2], discard[2].size()-1,
						 moveTo);
	case 4:
		return legalMove(discard[3].get(), discard[3], discard[3].size()-1,
						 moveTo);
	default:
		int cardFromHand = start - 5;
		if (cardFromHand >= hand.size())
			return false;
		return legalMove(hand.get(cardFromHand), hand, cardFromHand, moveTo);
	}
}
