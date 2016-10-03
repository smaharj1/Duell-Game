/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once
#include"player.h"
#include "Board.h"
#include"algorithm.h"
using namespace std;

class computer : public player
{
public:
	computer(int keys[], int size);
	computer(Board * board);
	~computer();
	Dice * play(Board * board);
	void printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition);
	Dice ** getDices() { return computerDices; }

private:
	Dice * computerDices[9];
};

