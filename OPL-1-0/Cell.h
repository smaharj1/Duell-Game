/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include"Dice.h"

class Cell
{
public:
	Cell();
	~Cell();
	Cell(Dice * d);

	void addDice(Dice * givenDice);
	bool isEmpty();

	Dice * getDice();
	void removeDice();

private:
	Dice * dice;
};

