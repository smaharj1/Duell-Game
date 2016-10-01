#pragma once
#include"Dice.h"

class TreeNode
{
public:
	TreeNode();
	~TreeNode();

private: 
	Dice * currentDice;
	TreeNode * previousNode;
	int row;
	int col;
};

