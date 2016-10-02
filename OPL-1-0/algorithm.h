#pragma once
#include"Board.h"
#include "TreeNode.h"
#include"location.h"
#include<vector>

class algorithm
{
public:
	algorithm();
	bool goDefence(Board * board, bool isComputer);

	void refreshPlayers(Board * board, bool isComputer);
	bool canEat(Board * board, bool isComputer);
	bool canMoveKing(Board * board, bool isComputer);
	bool kingInThreat(Board * board, bool isComputer);

	treeNode * getSuggestedMoves() { return suggestedMove; }
	location * getSuggestedLocation() { return suggestedNewLocation; }


private:
	

	treeNode * threateningNode;
	treeNode * suggestedMove;
	location * suggestedNewLocation;

	vector<treeNode *> currentPlayer;
	vector<treeNode *> opponentPlayer;

};