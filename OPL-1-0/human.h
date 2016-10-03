/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include"player.h"
#include"Board.h"
#include"algorithm.h"
using namespace std;

/*
	Child class of player class that is used for human players. It derives various functions such as play and get dices from player class.
*/
class human : public player
{
public:
	// Constructor that the keys and the size for the constructor.
	human(int keys[], int size);

	// Sets the class variables according to the board given.
	human(Board * board);

	~human();
	
	// Plays the human's turn for the game if the board is given and returns dice value if any die was eaten during the play/movement.
	Dice * play(Board * board);

	// Prints the move.
	void printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition);

	// Gets all the human dices that exits on the board.
	Dice ** getDices() { return humanDices; }



private:
	Dice * humanDices[9];

	bool validValues(char row, char col, char newRow, char newCol);
	void askForHelp(Board * board);
};

