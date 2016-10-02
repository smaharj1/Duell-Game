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
