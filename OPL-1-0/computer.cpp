/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "computer.h"

/* *********************************************************************
Function Name: computer
Purpose: Constructor to store the dices of the computer.

Parameters:
	keys, an integer array. It holds the values of the dice that needs to be saved.
	size, an integer. It holds the size of the keys array.

Return Value: none.

Local Variables:
	top, an integer. It holds the top of the dice.
	right, an integer. It holds the right side of the dice.
	front, an integer. It holds the front side of the dice. It is front facing to the player.
	mid, an integer. It holds the middle index of the size.

Algorithm:
	1. Compute the front face from given top and right
	2. Store the Dice in the array of computer's dices.

Assistance Received: none
********************************************************************* */
computer::computer(int keys[], int size) {
	// Initialize the faces of the dice.
	int top = 0, right = 0, front = 0;
	int mid = size / 2;

	// Loops through each key and computes the dice. Then, it stores it in the array.
	for (int index = 0; index < size; index++) {
		top = keys[index];
		right = FRONT_FACE;
	
		// Calls the static function from Dice class that computes the front face.
		front = Dice::computeFrontFace(top, right);

		// Here, right is technically front. We are considering it right to find an actual right.
		if (index == mid) {
			computerDices[index] = new Dice(true, 1, 1, 1);
		}
		else {
			computerDices[index] = new Dice(true, top, right, 7 - front);
		}

	}
}

/* *********************************************************************
Function Name: computer
Purpose: Constructor that is used if the serialization file is being loaded.

Parameters:
	board, a pointer. It holds the pointer to original board.

Return Value: none.

Local Variables:
	tmp, a pointer. It holds the pointer to the dice.
	diceIndex, an integer. It holds the index of the dice.

Algorithm: 
	1. Go through the board.
	2. In each cell, if computer dice is found, save it in the array.

Assistance Received: none
********************************************************************* */
computer::computer(Board * board) {
	Dice * tmp;
	int diceIndex = 0;
	for (int row = 0; row < board->getTotalRows(); row++) {
		for (int col = 0; col < board->getTotalColumns(); col++) {
			tmp = board->getCell(row, col)->getDice();
			if (tmp != NULL) {
				if (!tmp->isPlayerComputer()) {
					computerDices[diceIndex] = tmp;
					diceIndex++;
				}
			}
		}
	}

	// This nullifies the remaining dice locations. It means the dices are eaten.
	for (int i = diceIndex; i < 9; i++) {
		computerDices[i] = NULL;
	}
}

/* *********************************************************************
Function Name: ~computer
Purpose: Destructor.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
computer::~computer()
{
}

/* *********************************************************************
Function Name: printMove
Purpose: To print the move made by the computer using algorithm. It will print
	so that there are also explanations on each move made.

Parameters:
	givenDice, a pointer. It holds the pointer to the given dice.
	row, an integer. It holds the row number that are user friendly. Index starts at 1.
	column, an integer. It holds the column number that are user friendly. Index starts at 1.
	newRow, an integer. It holds the new row number that are user friendly. Index starts at 1.
	newColumn, an integer. It holds the new column number that are user friendly. Index starts at 1.
	condition, an enumerator. It holds the step taken by the algorithm.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void computer::printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition) {
	cout << "The computer picked " << givenDice->getValue() << " because ";

	// Checks the condition of movement chosen by computer and gives explanation accordingly.
	switch (condition) {
	case CanWin:
		cout << " it could make computer win the game." << endl;
		break;
	case CanEatKingsThreat:
		cout << " it removed the threat from the king by eating it." << endl;
		break;
	case CanEatOpponent:
		cout << " it ate the opponent's dice." << endl;
		break;
	case MoveKing:
		cout << " the king was going to die in next step and there was no way of protection." << endl;
		break;
	case PlaySafe:
		cout << " it is best to play safe. No one can eat the dice in this new location" << endl;
		break;
	}

	// Prints the explanations for frontal and lateral movements.
	int frontal = newRow - row;
	if (frontal < 0) {
		cout << "It moved frontal by " << abs(frontal) << " because it led to the current situation. " << endl;
	}
	else if (frontal >0) {
		cout << "It moved back by " << abs(frontal) << " because it led to the current situation. " << endl;
	}

	int side = newCol - column;
	if (side < 0) {
		cout << "It moved left by " << abs(side) << " because it led to the current situation. " << endl;
	}
	else if (side >0) {
		cout << "It moved right by " << abs(side) << " because it led to the current situation. " << endl;
	}

}

/* *********************************************************************
Function Name: play
Purpose: To play the computers move. It uses an algorithm that suggests the right
	move to make so that the computer can play offensively as well as defensively.

Parameters:
	board, a pointer. It holds the pointer to the board.

Return Value: Returns a dice if computer ate any dice.

Local Variables: 
	suggestedMove, a pointer. It points to the tree node that says which die to move.
	suggestedLocation, a pointer. It points to the location where the die needs to be moved.

Algorithm:
	1. Check if player can move.
	2. If no, check if king is in threat.
	3. If yes, check if threat can be eaten.
	4. If no, check if king can be moved.
	5. If no, then move on to eat other dices of opponent.
	6. If no dices to eat, take an offensive and safe step.

Assistance Received: none
********************************************************************* */
Dice * computer::play(Board * board) {
	algorithm algo(board, true);
	treeNode * suggestedMove;
	location * suggestedLocation;

	// First, check if the bot can win.
	if (algo.canWin()) {
		// Gets the suggested moves from algorithm.
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();

		// Prints the moves.
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanWin);

		// Moves the dice to the suggested location.
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// Defend the king first.
	if (algo.isKingInThreat()) {
		if (algo.canEatThreat()) {
			cout << "You tried to eat my king huh? Smart!" << endl << "Just kidding! This is for you, love! Rest In Peace!" << endl << endl;
			// Gets the suggested moves.
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			
			// Prints the move to be made.
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatKingsThreat);
			cout << "Mess is cleaned up" << endl;

			// Moves the dice to the suggested location.
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
		else if (algo.canMoveKing()) {
			// Try to move the king to escape.
			// Gets the suggested move.
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();

			// Prints the move.
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::MoveKing);
			
			// Moves the dice to desired location.
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
	}

	// If the king does not have any threat, try to eat other players
	if (algo.canEatOpponent()) {
		// Gets the suggested location.
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		cout << "-------How do you like them apples?---------" << endl;

		// Prints the move.
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatOpponent);
		
		// Moves the dice.
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// If nothing is attackable, move the dice closest to opponent where opponent can't eat.
	if (algo.safeOffense()) {
		// Gets the suggested move.
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();

		// Prints the move.
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::PlaySafe);
		
		// Moves the dice.
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	return NULL;
}


