/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "human.h"

/* *********************************************************************
Function Name: human
Purpose: Constructor to store the dices of the human.

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
human::human(int keys[], int size)
{
	// Initialize the faces of the dice.
	int top = 0, right = 0, front = 0;
	int mid = size / 2;

	// Loops through each key and computes the dice. Then, it stores it in the array.
	for (int index = 0; index < size; index++) {
		top = keys[index];
		right = 3;
		
		// Calls the static function from Dice class that computes the front face.
		front = Dice::computeFrontFace(top, right);

		// Here, right is technically front. We are considering it right to find an actual right.
		if (index == mid) {
			humanDices[index] = new Dice(false, 1, 1, 1);
		}
		else {
			humanDices[index] = new Dice(false, top, right, 7 - front);
		}

	}
}

/* *********************************************************************
Function Name: human
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
human::human(Board * board) {
	Dice * tmp;
	int diceIndex = 0;
	for (int row = 0; row < board->getTotalRows(); row++) {
		for (int col = 0; col < board->getTotalColumns(); col++) {
			tmp = board->getCell(row, col)->getDice();
			if (tmp != NULL) {
				if (!tmp->isPlayerComputer()) {
					humanDices[diceIndex] = tmp;
					diceIndex++;
				}
			}
		}
	}

	// This nullifies the remaining dice locations. It means the dices are eaten.
	for (int i = diceIndex; i < 9; i++) {
		humanDices[i] = NULL;
	}
}

/* *********************************************************************
Function Name: ~human
Purpose: Destructor.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
human::~human()
{

}

/* *********************************************************************
Function Name: askForHelp
Purpose: It initiates the algorithm to provide the user help with making the move.
	It prioritizes for first winning, then, saving the king if there are any threats
	then playing in the offense.

Parameters: 
	board, a pointer. It holds the pointer to the board.

Return Value: none.

Local Variables: 
	algo, an algorithm class. It holds the algorithm class that provides all the heuristic functionalities.
	suggestedMove, a treeNode. It holds the information of the die that should be moed.
	suggestedLocation, a location object. It holds the new location to move the die to.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void human::askForHelp(Board * board) {
	// Initializes the algorithm.
	algorithm algo(board, false);

	// Declares the suggestions.
	treeNode * suggestedMove;
	location * suggestedLocation;

	// First, check if the bot can win.
	if (algo.canWin()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();

		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanWin);
		return;
	}

	// Defend the king first.
	if (algo.isKingInThreat()) {
		if (algo.canEatThreat()) {
			
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatKingsThreat);
			return;
			
		}
		else if (algo.canMoveKing()) {
			// Try to move the king to escape.
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::MoveKing);
			return;
		}
	}

	// If the king does not have any threat, try to eat other players
	if (algo.canEatOpponent()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatOpponent);
		return;
	}

	// If nothing is attackable, move the dice closest to opponent where opponent can't eat.
	if (algo.safeOffense()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::PlaySafe);
		return;
	}

}

/* *********************************************************************
Function Name: askIfHelpNeeded
Purpose: To take user's input for if they need any help from the algorithm.

Parameters: none.

Return Value: Returns a character of user's input.

Local Variables: 
	userInput, a character. It holds user's input.

Algorithm: none.

Assistance Received: none
********************************************************************* */
char askIfHelpNeeded() {
	char userInput;
	cout << "Would you like some help (Y for yes, anything else for No)? ";
	cin >> userInput;

	return tolower(userInput);
}

/* *********************************************************************
Function Name: play
Purpose: To play the human's move. It asks user to input the coordinates of get help.

Parameters:
	board, a pointer. It holds the pointer to the board.

Return Value: Returns a dice if computer ate any dice.

Local Variables:
	row, an integer. It holds the row information.
	column, an integer. It holds the column information.
	newRow, an integer. It holds the new row information.
	newCol, an integer. It holds the new column information.
	direction, a character. It holds the direction information.

Algorithm:
	1. Ask user if they want help
	2. If no, let user choose the move

Assistance Received: none
********************************************************************* */
Dice * human::play(Board * board) {
	// Initialization of variables.
	row = -1; column = -1; newRow = -1; newCol = -1;
	char direction;

	cout << "It is your turn. Please make a move " << endl;
	board->setGodMode(false);

	// Asks for user's move
	do {
		char r, c, newR, newC;

		// Asks if the user needs any help from computer.
		char userInput = askIfHelpNeeded();
		if (userInput == 'y') {
			askForHelp(board);
		}

		// Asks for user's move.
		do {
			cout << "Enter your move? Please give coordinates from 1 1 to 8 9 :: ";
			cin >> r >> c;

			cout << "Enter the preferred destination from 1 1 to 8 9 :: ";
			cin >> newR >> newC;
			// Validates the coordinates entered by the user as to if they are inside the bounds and if they are digits.
		} while (!validValues(r, c, newR, newC));

		// Calculates the rows and columns as integers.
		row = r - '0';
		column = c - '0';
		newRow = newR - '0';
		newCol = newC - '0';

		// Convert user given input to array compatible input 
		row = board->getTotalRows()+1 - row;
		newRow = board->getTotalRows()+1 - newRow;
		paths[0] = true;
		paths[1] = true;

		// Performs all the validations.
	} while (!isMoveInBound(row, column, newRow, newCol) ||
		board->isLegal(row, column, newRow, newCol, false) == false ||
		board->isPathGood(row, column, newRow, newCol, paths) == false);

	// At this point, one of the path is valid. So, just check with user if they want any prefered direction.
	do {
		cout << "Do you want to move FRONTAL or LATERAL first? (F/L) :: ";
		cin >> direction;

		direction = tolower(direction);
		// path[0] is frontal movement.
		// If frontal movement is not possible, then, the lateral movement is chosen automatically, or vice versa.
		if ((direction == 'f')) {
			if (paths[0] == true) {
				cout << "Moving the dice frontally first..." << endl;
			}
			else {
				cout << "Dice cannot make frontal move first because of the distractions... Going lateral..." << endl;
				direction = 'l';
			}
		}
		else if (direction == 'l') {
			if (paths[1] == true) {
				cout << "Moving the dice laterally first..." << endl;
			}
			else {
				cout << "Dice cannot make lateral move first because of the distractions... Going frontal..." << endl;
				direction = 'f';
			}
		}
		else {
			cout << "Invalid character entered. Please enter it again" << endl;
		}
	} while (direction != 'f' && direction != 'l');


	// If it returns true while moving, it means that the player moving won other player's dice.
	Dice * returnedDice = board->move(row, column, newRow, newCol, direction);

	// Prints the activity.
	printActivity(9-row, column, 9-newRow, newCol, false, direction);

	return returnedDice;
}

/* *********************************************************************
Function Name: validValues
Purpose: To validate if the given values are digits or not.

Parameters: 
	row, a character. It holds the row number. It is human friendly. It starts at 0.
	col, a character. It holds the column number. It is human friendly. It starts at 0.
	newRow, a character. It holds the new row number. It is human friendly. It starts at 0.
	newCol, a character. It holds the new column number. It is human friendly. It starts at 0.

Return Value: Returns true if all of them are digits

Local Variables: 
	res, boolean. it holds the returning value.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool human::validValues(char row, char col, char newRow, char newCol) {
	bool res = isdigit(row) && isdigit(col) && isdigit(newRow) && isdigit(newCol);
	if (!res) {
		cout << "Some of the values entered are not numbers" << endl;
	}
	return res;
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
void human::printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition) {
	cout << "You can move " << givenDice->getValue() << " at (" << row << "," << column << ") to (" << newRow << "," << newCol << ") roll because ";

	switch (condition) {
	case CanWin:
		cout << " it could make you win the game." << endl;
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
}