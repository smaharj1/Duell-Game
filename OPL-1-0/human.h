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

class human : public player
{
public:
	human();
	human(int keys[], int size);
	human(Board * board);
	~human();
	Dice * play(Board * board);
	void printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition);

	Dice ** getDices() { return humanDices; }



private:
	Dice * humanDices[9];

	bool validValues(char row, char col, char newRow, char newCol);
	void askForHelp(Board * board);
};

