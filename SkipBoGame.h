#ifndef _SKIPBOGAME_H
#define _SKIPBOGAME_H
#include "Player.h"

class SkipBoGame
{

public:
	SkipBoGame(int num_player, int num_stock, std::vector<Card> deck,
			std::string rand);
	SkipBoGame(string shuffle, string directory);
	void shuffle(std::vector<Card> & draw);
	std::string toString() const;
	void display() const;
	int getNumPlayers() const{return nump;}
	void deal(int num_player, int num_stock);
	std::pair<bool, bool> turn(int curp);
	void playGame(std::vector<Card> aside);
	int numStock(){return peep[0].stockNum();}
	void displayP();
	void gameOver()
	{
		std::cout << "GAME OVER - " << peep[curp].getName() << " wins!" << std::endl;
	}
	void saveGame(std::string);
	//bool compareTo(Player p1, Player p2);

private:
	int nump, curp;
	std::string rand;
	std::vector<Player> peep;
	DrawPile drawpile;
	std::vector<BuildPile> build;
};
#endif
