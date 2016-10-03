/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#pragma once

#include"Dice.h"

/*
	This class acts as an individual square of the board that can hold a die. This class will have fixed coordinates and in future will have location
	in built.
*/
class Cell
{
public:
	// Constructor for the class.
	Cell();
	~Cell();

	// Constructor for the class if the die is given.
	Cell(Dice * givenDice);

	// Sets the dice and returns true if it successfully performs the operation.
	bool setDice(Dice * givenDice);

	// Checks if the cell is empty.
	bool isEmpty();

	// Gets the die in the cell.
	Dice * getDice();

	// Removes the die from the cell.
	void removeDice();

private:
	// private variable that holds the die.
	Dice * dice;
};

