/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "TreeNode.h"


/* *********************************************************************
Function Name: treeNode
Purpose: Default constructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
treeNode::treeNode(Dice * d, int row, int col) {
	currentDice = d;
	currentLocation = new location(row, col);
	previousNode = NULL;
}

/* *********************************************************************
Function Name: treeNode
Purpose: Destructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
treeNode::~treeNode()
{
}
