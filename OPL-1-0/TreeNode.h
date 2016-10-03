/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/

#pragma once
#include"Dice.h"
#include "location.h"

/*
	This class holds the dice and the current location of the dice.
*/
class treeNode
{
public:
	// The tree node constructor that will take in the dice and location.
	treeNode(Dice * d, int row, int col);
	~treeNode();

	// Gets the location of the dice.
	location * getLocation() { return currentLocation; }

	// Gets the row.
	int getRow() { return currentLocation->getRow(); }

	// Gets the column.
	int getColumn() { return currentLocation->getColumn(); }

	// Gets the pointer to the dice.
	Dice * getDice() { return currentDice; }

private: 
	// Private variables that hold the current dice and location and also previous 
	Dice * currentDice;
	treeNode * previousNode;
	location *currentLocation;
};

