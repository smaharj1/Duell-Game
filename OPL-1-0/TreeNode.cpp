/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "TreeNode.h"

treeNode::treeNode()
{
}

treeNode::treeNode(Dice * d, int row, int col) {
	currentDice = d;
	currentLocation = new location(row, col);
	previousNode = NULL;
}


treeNode::~treeNode()
{
}
