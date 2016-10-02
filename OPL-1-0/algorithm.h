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

	void refreshPlayers( bool isComputer);
	bool canEatThreat();
	bool canMoveKing(bool isComputer);
	bool kingInThreat();
	bool canEatOpponent();

	bool canWin();
	bool safeOffense();

	bool canEat(vector<treeNode *> current, treeNode * diceToEat);
	bool canReachLocation(vector<treeNode *> playerNodes, int row, int col);

	treeNode * getSuggestedMoves() { return suggestedMove; }
	location * getSuggestedLocation() { return suggestedNewLocation; }


private:
	treeNode * getCurrentPlayersKing();
	treeNode * getOpponentsKing();

	Board * board;

	treeNode * threateningNode;
	treeNode * suggestedMove;
	location * suggestedNewLocation;

	vector<treeNode *> currentPlayer;
	vector<treeNode *> opponentPlayer;

	bool algoForComputer;

};