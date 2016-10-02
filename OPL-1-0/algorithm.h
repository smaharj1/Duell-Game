#pragma once
#include"Board.h"
#include "TreeNode.h"
#include"location.h"
#include<vector>

class algorithm
{
public:
	algorithm();
	algorithm(Board * board, bool isComputer);
	bool goDefence(Board * board, bool isComputer);

	void refreshPlayers(Board * board, bool isComputer);
	bool canEat(Board * board);
	bool canMoveKing(Board * board);
	bool kingInThreat(Board * board);

	treeNode * getSuggestedMoves() { return suggestedMove; }
	location * getSuggestedLocation() { return suggestedNewLocation; }


private:
	treeNode * getCurrentPlayersKing();
	treeNode * getOpponentsKing();

	treeNode * threateningNode;
	treeNode * suggestedMove;
	location * suggestedNewLocation;

	vector<treeNode *> currentPlayer;
	vector<treeNode *> opponentPlayer;

};