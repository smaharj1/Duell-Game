/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include"algorithm.h"

/* *********************************************************************
Function Name: algorithm
Purpose: This is the constructor of the class

Parameters:
	board, a pointer to the original board. It holds the address of the board class.
	isComputer, a boolean. It holds the value that indicates if the player is a computer.

Return Value: None.

Local Variables: None.

Algorithm:
	1) It initializes all the class variables.

Assistance Received: none
********************************************************************* */
algorithm::algorithm(Board * board, bool isComputer) {
	this->board = board;
	algoForComputer = isComputer;
	refreshPlayers();
	

	nullifySuggestions();
	threateningNode = NULL;
}

/* *********************************************************************
Function Name: nullifySuggestions
Purpose: To reset the values of suggested moves that are stored as class variables.

Parameters: None.

Return Value: None.

Local Variables: none.

Algorithm:
	1) Sets suggested moves to null.

Assistance Received: none
********************************************************************* */
void algorithm::nullifySuggestions() {
	// Resets the suggested moves to NULL.
	suggestedMove = NULL;
	suggestedNewLocation = NULL;
}

/* *********************************************************************
Function Name: refreshPlayers
Purpose: To reset the vector of both players dice nodes that are in the board.

Parameters: none

Return Value: none

Local Variables: none

Algorithm:
	1) Goes through each square of the board.
	2) Stores the dice found to the designated vector of player dices.

Assistance Received: none
********************************************************************* */
void algorithm::refreshPlayers() {
	// Resets the dices of current and opponent players.
	opponentPlayer.clear();
	currentPlayer.clear();

	// Loops through each square in the board and adds the dices to the vectors of current and 
	// opponent players accordingly.
	for (int row = 0; row < board->getTotalRows(); row++) {
		for (int col = 0; col < board->getTotalColumns(); col++) {
			if (!board->getCell(row, col)->isEmpty()) {
				Dice * d = board->getCell(row, col)->getDice();

				// Checks if the dice in a square is of same players as of provided player.
				// If not, it adds the dice to opponent's vector.
				if (d->isPlayerComputer() != algoForComputer) {
					opponentPlayer.push_back(new treeNode(d, row, col));
				}
				else {
					currentPlayer.push_back(new treeNode(d, row, col));
				}
			}
		}
	}
}

/* *********************************************************************
Function Name: canMoveKing
Purpose: To check if king dice can be moved to its sides. This occurs if
	there is a threat to the king and there is no options other than to move king.

Parameters: none

Return Value: Returns true if king can be moved to one of the squares.

Local Variables: 
	playersKing, pointer that points to the king's square.

Algorithm:
	1) Find four sides of the king.
	2) Check the first place the king can be moved among its four directions.

Assistance Received: none
********************************************************************* */
bool algorithm::canMoveKing() {
	// Holds the node of current players king.
	treeNode * playerKing = getCurrentPlayersKing();

	// Check if it returns NULL.
	if (playerKing == NULL) {
		return false;
	}
	
	// Holds the 4 sides of the king's current location.
	int front = playerKing->getRow()+1;
	int back = playerKing->getRow() - 1;
	int left = playerKing->getColumn() + 1;
	int right = playerKing->getColumn() - 1;

	// Resets the suggestions before calculation.
	nullifySuggestions();

	// Checks if the king can move forward. King is moved if there is an imminent threat to the king.
	if (front < board->getTotalRows() && front >= 0) {
		// If the move is legal, then, it stores the move info to suggested move.
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), front, playerKing->getColumn(), algoForComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(front, playerKing->getColumn());
			return true;
		}
	}
	
	// Checks if the king can move backward.
	if (back < board->getTotalRows() && back >= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), back, playerKing->getColumn(), algoForComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(back, playerKing->getColumn());
			return true;
		}
	}

	// Checks if the king can move left.
	if (left < board->getTotalColumns() && left >= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), playerKing->getRow(), left, algoForComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(playerKing->getRow(), left);
			return true;
		}
	}

	// Checks if the king can move right.
	if (right < board->getTotalColumns() && right>= 0) {
		if (board->isLegalAlgo(playerKing->getRow(), playerKing->getColumn(), playerKing->getRow(), right, algoForComputer)) {
			suggestedMove = playerKing;
			suggestedNewLocation = new location(playerKing->getRow(), right);
			return true;
		}
	}

	// Returns false if king cannot be moved
	return false;
}


/* *********************************************************************
Function Name: getCurrentPlayersKing
Purpose: To get the node of current player's king.

Parameters: none

Return Value: Returns the pointer of the node of player's king.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
treeNode * algorithm::getCurrentPlayersKing() {
	// Loops through the vector of dices of current player and returns the king node.
	for (int i = 0; i < currentPlayer.size(); i++) {
		if (currentPlayer[i]->getDice()->isPlayerKing()) {
			return currentPlayer[i];
		}
	}

	// If there is no king, it returns NULL.
	return NULL;
}

/* *********************************************************************
Function Name: getOpponentsKing
Purpose: To get the opponents king dice node.

Parameters: none.

Return Value: Returns the pointer to the opponents king's dice

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
treeNode * algorithm::getOpponentsKing() {
	// Loops throught the vector of dices of opponent player and returns the king node.
	for (int i = 0; i < opponentPlayer.size(); i++) {
		if (opponentPlayer[i]->getDice()->isPlayerKing()) {
			return opponentPlayer[i];
		}
	}

	// Returns null if king is not found.
	return NULL;
}

/* *********************************************************************
Function Name: canEatThreat
Purpose: To check if the threat to current player's king can be eaten by any other dices.

Parameters: none.

Return Value: Returns true if the threat to the king can be eaten.

Local Variables: none.

Algorithm:
	1) Loop through each of current players dices.
	2) Checks if the dices can eat the threat.

Assistance Received: none
********************************************************************* */
bool algorithm::canEatThreat() {
	// Checks if the there is a threat just to make sure.
	if (threateningNode == NULL) {
		return false;
	}

	// Resets the suggestions.
	nullifySuggestions();

	// At this point, threatening node is not null.
	// Loop through each dice of players and see if you can eat threatening node.
	if (canEat(currentPlayer, threateningNode)) {
		return true;
	}
	
	// Returns false if the threat cannot be eaten.
	return false;
}


/* *********************************************************************
Function Name: kingInThreat
Purpose: To check if current player's king is in threat by the opponent.

Parameters: none.

Return Value: Returns true if the king is in threat by the opponent.

Local Variables: 
	playerKing, pointer that points towards current player's king.

Algorithm:
	1. Loop through each opponent player's dices
	2. Check if they can legally move to kings location.

Assistance Received: none
********************************************************************* */
bool algorithm::isKingInThreat() {
	// Holds the node of king's dice.
	treeNode * playerKing = getCurrentPlayersKing();

	// If it is null, return false.
	if (playerKing == NULL) {
		return false;
	}

	// Check if each of opponent players can legally move to king's location
	for (int i = 0; i < opponentPlayer.size(); i++) {
		treeNode * tempNode = opponentPlayer[i];
		if (board->checkPathForAlgo(tempNode->getRow() , tempNode->getColumn(), playerKing->getRow(), playerKing->getColumn() , true)) {
			cout << "King is in imminent threat by " << opponentPlayer[i]->getDice()->getValue() << endl;
			threateningNode = opponentPlayer[i];
			return true;
		}
	}
	
	threateningNode = NULL;
	return false;
}


/* *********************************************************************
Function Name: canWin
Purpose: To check if the current player can win the game by eating the king or going to 
	the winning location.

Parameters: none.

Return Value: Returns true if current player can win.

Local Variables: 
	opponentKing, pointer to opponent's king dice.
	winLocation, pointer towards the winning location depending on the player.

Algorithm:
	1. Loop through each of current player's dices.
	2. Check if that dice can reach the opponent king's location or winning location.

Assistance Received: none
********************************************************************* */
bool algorithm::canWin() {
	// Holds the values of opponent's king location and winning location case.
	treeNode * opponentKing = getOpponentsKing();
	location * winLocation = algoForComputer ? new location(7, 4) : new location(0, 4);
	
	// Resets the suggestions before computation.
	nullifySuggestions();

	// Loops through current players dices and checks if any dice can make the player win the game.
	for (int index = 0; index < currentPlayer.size(); index++) {
		treeNode * tempNode = currentPlayer[index];

		// Checks if either winning location can be reached or king can be eaten.
		if (board->checkPathForAlgo(tempNode->getRow(), tempNode->getColumn(), opponentKing->getRow(), opponentKing->getColumn(), true)) {
			suggestedMove = tempNode;
			suggestedNewLocation = opponentKing->getLocation();
			return true;
		}
		else if (board->checkPathForAlgo(tempNode->getRow(), tempNode->getColumn(), winLocation->getRow(), winLocation->getColumn(), true)) {
			suggestedMove = tempNode;
			suggestedNewLocation = winLocation;
			return true;
		}
	}

	// Returns false if this is not the winning case.
	return false;
}

/* *********************************************************************
Function Name: canEat
Purpose: To check if any current player's dice can eat the opponent.

Parameters:
	current, vector of dices pointers. It holds all the dices of the any player passed.
	diceToEat, pointer to treeNode. It holds the dice that is to be eaten.

Return Value: Returns true if the dice specified can be eaten.

Local Variables: 
	tempNode, pointer that holds a single treeNode info.

Algorithm:
	1. Go through each dices
	2. Check if the dice that needs to be eaten can be reached by this dice.

Assistance Received: none
********************************************************************* */
bool algorithm::canEat(vector<treeNode *> current, treeNode * diceToEat) {
	nullifySuggestions();

	// Loops through all the current node dices and checks if it can eat the dice mentioned.
	for (int index = 0; index < current.size(); index++) {
		treeNode * tempNode = current[index];
		if (board->checkPathForAlgo(tempNode->getRow(), tempNode->getColumn(), diceToEat->getRow(), diceToEat->getColumn(), true)) {
			suggestedMove = tempNode;
			suggestedNewLocation = diceToEat->getLocation();
			return true;
		}
	}

	// Returns false if it cannot eat the dice.
	return false;
}

/* *********************************************************************
Function Name: canEatOpponent
Purpose: To check if the opponent can be eaten and set the opponent that can be eaten
	as suggestion.

Parameters: none.

Return Value: Returns true if opponent can be eaten.

Local Variables: 
	tempNode, pointer that holds a single treeNode info.

Algorithm:
	1. Go through each dices of current player and check if opponent dices can be eaten.

Assistance Received: none
********************************************************************* */
bool algorithm::canEatOpponent() {
	nullifySuggestions();

	// Goes to each opponent and check if any current player dices can eat the opponent.
	// Return true if it can eat.
	for (int oppIndex = 0; oppIndex < opponentPlayer.size(); oppIndex++) {
		treeNode * tmpNode = opponentPlayer[oppIndex];

		if (canEat(currentPlayer, tmpNode)) {
			return true;
		}
	}

	// Returns false if the opponent's dices cannot be eaten.
	return false;
}


/* *********************************************************************
Function Name: canReachLocation
Purpose: To check if any of the current player's dices can reach the location specified.
	It puts the dice that can be moved as a suggestion.

Parameter:
	playerNodes, pointer. It holds the dices of the player.
	row, an integer. It holds the row number that needs to be reached.
	column, an integer. It holds the column number that needs to be reached.

Return Value: Returns true if the location can be reached by any dices.

Local Variables:
	tempNode, pointer that holds a single treeNode info.

Algorithm:
	1. Go through each dice and see if the path is legal to move to desired location.

Assistance Received: none
********************************************************************* */
bool algorithm::canReachLocation(vector<treeNode *> playerNodes, int row, int col) {
	nullifySuggestions();
	
	// Checks if the location can be reached by the given tree nodes.
	for (int index = 0; index < playerNodes.size(); index++) {
		treeNode * tempNode = playerNodes[index];
		if (board->checkPathForAlgo(tempNode->getRow(), tempNode->getColumn(), row, col, true)) {
			suggestedMove = tempNode;
			suggestedNewLocation = new location(row,col);
			return true;
		}
	}

	// Returns false if the location cannot be reached.
	return false;
}

/* *********************************************************************
Function Name: safeOffense
Purpose: To find a dice of current player and a location on the board which moves like an 
	offense but yet manages not to be eaten by the opponent.

Parameters: none.

Return Value: Returns true if there is a safe offense location.

Local Variables: none.

Algorithm:
	1. Goes through each location on the board starting from opponents locations.
	2. Finds the first location that is safe.

Assistance Received: none
********************************************************************* */
bool algorithm::safeOffense() {
	nullifySuggestions();

	// Find the closest location on the opponent's side where its safe to keep players dice.
	// It computes the location such a way that opponent would be able to eat it.
	if (algoForComputer) {
		for (int row = board->getTotalRows() - 1; row >= 0; row--) {
			for (int col = 0; col < board->getTotalColumns(); col++) {
				// Check if any opponent player nodes can reach this location. 
				// If yes, then move on. If no, then check if current player can move their dice to this location.
				if (!canReachLocation(opponentPlayer, row, col)) {
					if (canReachLocation(currentPlayer, row, col)) {
						// At this point, the suggested move and location will already have been set.
						return true;
					}
				}
			}
		}
	}
	else {
		for (int row = 0; row < board->getTotalRows(); row++) {
			for (int col = 0; col < board->getTotalColumns(); col++) {
				// Check if any opponent player nodes can reach this location. 
				// If yes, then move on. If no, then check if current player can move their dice to this location.
				if (!canReachLocation(opponentPlayer, row, col)) {
					if (canReachLocation(currentPlayer, row, col)) {
						// At this point, the suggested move and location will already have been set.
						return true;
					}
				}
			}
		}
	}

	// Return false if there are no safe locations on the board.
	return false;
}