#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include "Pile.h"
#include "Card.h"
#include "Hand.h"
#include "BuildPile.h"
#include "DrawPile.h"
#include "StockPile.h"
#include "DiscardPile.h"

using std::string;

class Player
{
  public:
	Player(string n, std::vector<BuildPile> *b, DrawPile *dra) : name(n)
	{
		draw = dra;
		build = b;
		for (int i = 0; i < 4; i++)
			discard.push_back(DiscardPile());
	}
	Player(string n, StockPile s, Hand d, std::vector<DiscardPile> dis) : name(n), stock(s), hand(d), discard(dis) {}

	void display() const;
	void setBuild(std::vector<BuildPile> *b) { build = b; }
	void setDraw(DrawPile *dra) { draw = dra; }
	std::string toString() const;
	std::pair<bool, bool> makePlay(std::string command);
	bool move(int start, char end);
	bool legalMove(Card toMove, Pile &start, int index, Pile *end);
	void drawCards();
	int stockNum() { return stock.size(); }
	void addStock()
	{
		stock.addCard(draw->Pile::removeCard());
	}
	bool won()
	{
		return stock.size() == 0;
	}
	string getName() const
	{
		return name;
	}
	bool handEmpty() { return hand.size()==0; }

  private:
	string name;
	StockPile stock;
	Hand hand;
	std::vector<DiscardPile> discard;
	std::vector<BuildPile> *build;
	DrawPile *draw;
};

#endif
