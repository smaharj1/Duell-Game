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

/*
	This class consists various algorithmic functions split up individually such that it can be made as tough as the user wants.
*/
class algorithm
{
public:
	// Constructor for the class.
	algorithm(Board * board, bool isComputer);

	// Refreshes the suggestions from the algorithm to make the movements.
	void refreshPlayers();

	// Checks if the threat to the king can be eaten.
	bool canEatThreat();

	// Checks if the king can be moved to remove the threat.
	bool canMoveKing();

	// Checks if there is a threat to the king.
	bool isKingInThreat();

	// Checks if opponent players can be eaten with any of players dices.
	bool canEatOpponent();

	// Checks if the player can win the game.
	bool canWin();

	// CHecks if the player can play safe offense.
	bool safeOffense();

	// Checks if the dice can be eaten by collection of dices provided.
	bool canEat(vector<treeNode *> current, treeNode * diceToEat);

	// Checks if particular location can be reached by any dices provided.
	bool canReachLocation(vector<treeNode *> playerNodes, int row, int col);

	// Gets the suggested move and suggested location.
	treeNode * getSuggestedMoves() { return suggestedMove; }
	location * getSuggestedLocation() { return suggestedNewLocation; }

	// Returns if the algorithm is being run for the computer.
	bool isAlgoForComputer() { return algoForComputer; }

private:
	// Returns the current player is a king.
	treeNode * getCurrentPlayersKing();

	// Returns the king of opponent.
	treeNode * getOpponentsKing();

	// Resets the suggestions by the algorithm.
	void nullifySuggestions();

	// private variables that holds the information of the boad and suggested moves.
	Board * board;
	treeNode * threateningNode;
	treeNode * suggestedMove;
	location * suggestedNewLocation;
	bool algoForComputer;

	// Holds the vectors of dices of current and opponent players.
	vector<treeNode *> currentPlayer;
	vector<treeNode *> opponentPlayer;
};