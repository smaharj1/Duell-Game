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
	bool canEatThreat(Board * board);
	bool canMoveKing(Board * board, bool isComputer);
	bool kingInThreat(Board * board);
	bool canEatOpponent(Board * board);

	bool canWin(Board * board);

	bool canEat(Board *board,treeNode * diceToEat);

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

	bool algoForComputer;

};