CC=g++
CFLAGS=-std=c++11 -pedantic -Wall -Wextra -g

skipbo: SkipBoGame.o Player.o main.o StockPile.o Hand.o DiscardPile.o BuildPile.o PlayPile.o FaceUpPile.o Pile.o DrawPile.o Card.o
	$(CC) -o skipbo SkipBoGame.o Player.o main.o StockPile.o Hand.o PlayPile.o BuildPile.o PlayPile.o FaceUpPile.o Pile.o Card.o DrawPile.o

SkipBoGame.o: SkipBoGame.cpp Player.h
	$(CC) $(CFLAGS) -c SkipBoGame.cpp

Player.o: Player.cpp DiscardPile.h Hand.h StockPile.h BuildPile.h
	$(CC) $(CFLAGS) -c Player.cpp

main.o: main.cpp SkipBoGame.h
	$(CC) $(CFLAGS) -c main.cpp

#StockPile.o: StockPile.cpp
#	$(CC) $(CFLAGS) -c StockPile.cpp

Hand.o: Hand.cpp
	$(CC) $(CFLAGS) -c Hand.cpp

#PlayPile.o: PlayPile.cpp
#	$(CC) $(CFLAGS) -c PlayPile.cpp

BuildPile.o: BuildPile.cpp
	$(CC) $(CFLAGS) -c BuildPile.cpp

#DiscardPile.o: DiscardPile.cpp
#	$(CC) $(CFLAGS) -c DiscardPile.cpp

FaceUpPile.o: FaceUpPile.cpp
	$(CC) $(CFLAGS) -c FaceUpPile.cpp

Pile.o: Pile.cpp Card.h
	$(CC) $(CFLAGS) -c Pile.cpp

DrawPile.o: DrawPile.cpp
	$(CC) $(CFLAGS) -c DrawPile.cpp

Card.o: Card.cpp
	$(CC) $(CFLAGS) -c Card.cpp

clean:
	rm -f *.o skipbo
