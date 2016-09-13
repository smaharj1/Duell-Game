#pragma once

#include"Dice.h"

class Cell
{
public:
	Cell();
	~Cell();
	Cell(Dice * d);

	bool addDice(Dice * givenDice);
	bool isEmpty();

	Dice * getDice();
	void removeDice();

private:
	Dice * dice;
};

