#pragma once
#include"Dice.h"
#include "location.h"

class treeNode
{
public:
	treeNode();
	treeNode(Dice * d, int row, int col);
	~treeNode();

	location * getLocation() { return currentLocation; }
	int getRow() { return currentLocation->getRow(); }
	int getColumn() { return currentLocation->getColumn(); }
	Dice * getDice() { return currentDice; }

private: 
	Dice * currentDice;
	treeNode * previousNode;
	location *currentLocation;
};

