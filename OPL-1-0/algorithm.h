/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/

#pragma once
#include"Board.h"
#include "TreeNode.h"
#include"location.h"
#include<vector>

class algorithm
{
public:
	algorithm(Board * board, bool isComputer);

	void refreshPlayers( bool isComputer);
	bool canEatThreat();
	bool canMoveKing();
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
	void nullifySuggestions();

	Board * board;

	treeNode * threateningNode;
	treeNode * suggestedMove;
	location * suggestedNewLocation;
	bool algoForComputer;

	vector<treeNode *> currentPlayer;
	vector<treeNode *> opponentPlayer;

	

};