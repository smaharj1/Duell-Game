/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "Board.h"

/* *********************************************************************
Function Name: Board
Purpose: Default Constructor

Parameters: none.

Return Value: none.

Local Variables: 
	d, pointer of Dice. It temporarily creates a new dice.

Algorithm:
	1. Randomly initialize the board with very basic dices.

Assistance Received: none
********************************************************************* */
Board::Board()
{
	// Goes through the whole board of cell and initializes the board.
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			Dice * d;
			if (i == 0) {
				d = new Dice("C21");
				board[i][j] = new Cell(d);
			}
			else if (i == ROWS - 1) {
				d = new Dice("H21");
				board[i][j] = new Cell(d);
			}
			else {
				board[i][j] = new Cell();
			}
		}
	}

	// Initializes god mode as false.
	isGodMode = false;
}

/* *********************************************************************
Function Name: Board
Purpose: Constructor for opening given file.

Parameters: 
	human, pointer of pointer of Dice array. It holds the dice array of human.
	bot,pointer of pointer of Dice array. It holds the dice array of computer.
	size, 

Return Value: none.

Local Variables: none.

Algorithm:
	1. Puts the dices as given by the user on the board.

Assistance Received: none
********************************************************************* */
Board::Board(Dice ** human, Dice ** bot) {
	// Goes through the whole board and initializes the new board according to the dices given.
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (i == 0) {
				board[i][j] = new Cell(bot[j]);
			}
			else if (i == ROWS - 1) {
				board[i][j] = new Cell(human[j]);
			}
			else {
				board[i][j] = new Cell();
			}
		}
	}

	isGodMode = false;
}

/* *********************************************************************
Function Name: Board
Purpose: Destructor for class.

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Board::~Board()
{
}

/* *********************************************************************
Function Name: setGodMode
Purpose: To set the god mode to let the class know that this is automated case.
	It changes the way board errors are handled.

Parameters: 
	given, a boolean. It holds the value of god mode as provided by user.

Return Value: Returns true if successfully changed the value.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Board::setGodMode(bool given) {
	// sets the god mode.
	isGodMode = given;
	return true;
}

/* *********************************************************************
Function Name: setBoard
Purpose: To set the board according to the given values by the user.
	This will change the locations of the dice on the board.

Parameters:
	tempBoard[][], a string of board values. It holds 2D array of values that should fill the board.

Return Value: Returns true if it successfully fills the board.

Local Variables:
	d, pointer of dice. It helps create Dices to put on the board squares.

Algorithm:
	1. Loops through each square and fills it with the values gotten from user.

Assistance Received: none
********************************************************************* */
bool Board::setBoard(string tempBoard[][9]) {
	// Loops through each cell and stores the dices.
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (tempBoard[i][j] == "0") {
				board[i][j] = new Cell();
			}
			else {
				Dice * d = new Dice(tempBoard[i][j]);
				board[i][j] = new Cell(d);
			}
		}
	}

	return true;
}

/* *********************************************************************
Function Name: move
Purpose: To move the dice from the given row and column to the desired row and column.
	Important note here is that the locations received are human readable. So, indexing 
	starts from 1 instead of 0.

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.
	direction, a character. It holds the character of the direction to move first.

Return Value: Returns the pointer to the dice that has been eaten if any. Else, returns null.

Local Variables: 
	diceAte, a pointer to the dice. It holds the dice that is eaten after the movement. 
	isComputer, boolean. It holds if the player is computer or not.
	frontal, an integer. It holds the total frontal value of movement.
	side, an integer. It holds the side value of the movement.

Algorithm:
	1. Compute the frontal movement. Frontal and backward are calculated as positive/negative.
	2. Compute the side movement. 
	3. If computer, move front means move down and if human, vice versa.
	4. Same as above for lateral movement.
	5. Roll dices with the computed values.
	6. Move the dice to different cells.

Assistance Received: none
********************************************************************* */
Dice * Board::move(int row, int column, int newRow, int newCol, char direction) {
	Dice * diceAte = NULL;

	// Holds if the player is computer or human.
	bool isComputer = board[row-1][column-1]->getDice()->isPlayerComputer();

	// If the cell in the board is empty, return that it is empty.
	int frontal = newRow - row;
	int side = newCol - column;
	
	if (!isComputer) {
		if (direction == 'f') {
			// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
			for (int i = 0; i < abs(frontal); i++) {
				frontal < 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
					board[row - 1][column - 1]->getDice()->moveBackward();

			}

			// Checks if the dice is rolled right or left and assigns the rolling accordingly.
			for (int i = 0; i < abs(side); i++) {
				side > 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
					board[row - 1][column - 1]->getDice()->moveLeft();

			}
		}
		else {
			// Checks if the dice is rolled right or left and assigns the rolling accordingly.
			for (int i = 0; i < abs(side); i++) {
				side > 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
					board[row - 1][column - 1]->getDice()->moveLeft();
			}

			// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
			for (int i = 0; i < abs(frontal); i++) {
				frontal < 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
					board[row - 1][column - 1]->getDice()->moveBackward();
			}			
		}
	}
	else {
		if (direction == 'f') {
			// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
			for (int i = 0; i < abs(frontal); i++) {
				frontal > 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
					board[row - 1][column - 1]->getDice()->moveBackward();

			}

			// Checks if the dice is rolled right or left and assigns the rolling accordingly.
			for (int i = 0; i < abs(side); i++) {
				side < 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
					board[row - 1][column - 1]->getDice()->moveLeft();

			}
		}
		else {
			// Checks if the dice is rolled right or left and assigns the rolling accordingly.
			for (int i = 0; i < abs(side); i++) {
				side < 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
					board[row - 1][column - 1]->getDice()->moveLeft();

			}

			// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
			for (int i = 0; i < abs(frontal); i++) {
				frontal > 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
					board[row - 1][column - 1]->getDice()->moveBackward();

			}
		}
	}

	// Adds the dice to the Cell and removes the dice from previous location.
	if (!board[newRow - 1][newCol - 1]->isEmpty()) {
		//cout << "Dice is eaten!" << endl << endl;
		diceAte = board[newRow - 1][newCol - 1]->getDice();
		board[newRow - 1][newCol - 1]->removeDice();
	}
	board[newRow-1][newCol-1]->setDice(board[row - 1][column - 1]->getDice());
	board[row - 1][column - 1]->removeDice();

	return diceAte;
}

/* *********************************************************************
Function Name: isLegal
Purpose: To check if the movement from one location to another is legal according to players.
	Verifies if the selections are empty, replacing own player, or moving others dice. 

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.
	direction, a character. It holds the character of the direction to move first.

Return Value: Returns true if the movement is legal.

Local Variables:
	isComputer, a boolean. It holds the value of if the player is computer.

Algorithm:
	1. Check if the selection made is empty.
	2. Check if current player is trying to move other player's dice.
	3. Check if current player is trying to remove its own player.

Assistance Received: none
********************************************************************* */
bool Board::isLegal(int row, int column, int newRow, int newCol, bool playerIsComputer) {

	// If the cell in the board is empty, return that it is empty.
	if (board[row - 1][column - 1]->isEmpty()) {
		if (!isGodMode) {
			cout << "The selection is empty." << endl;
		}
		isGodMode = false;
		return false;
	}

	// Holds if the player is computer or human.
	bool isComputer = board[row - 1][column - 1]->getDice()->isPlayerComputer();

	// Check if the the user is trying to move other player's dice.
	if (playerIsComputer != isComputer) {
		if (!isGodMode) {
			cout << "You cannot move other player's dice." << endl;
		}
		isGodMode = false;
		return false;
	}

	// Checks if the user is trying to replace their own player by the movement.
	if (!board[newRow - 1][newCol - 1]->isEmpty()) {
		if ((board[row - 1][column - 1]->getDice()->isPlayerComputer() && board[newRow - 1][newCol - 1]->getDice()->isPlayerComputer()) ||
			!board[row - 1][column - 1]->getDice()->isPlayerComputer() && !board[newRow - 1][newCol - 1]->getDice()->isPlayerComputer()) {
			if (!isGodMode) { cout << "You cannot replace your own player" << endl; }
			isGodMode = false;
			return false;
		}
	}

	isGodMode = false;
	return true;
}

/* *********************************************************************
Function Name: isPathGood
Purpose: To check if the path is good. It checks if there are any distractions on the way.

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.
	correctPaths[], a boolean passed as reference. It holds the boolean values for if both frontal
		and lateral moves can be made

Return Value: Returns true if the path is possible.

Local Variables:
	frontal, an integer. It holds the total frontal movement that needs to be made.
	side,  an integer. It holds the lateral movement needed.

Algorithm:
	1. Make a frontal move first and then lateral. 
	2. Store if the path is possible.
	3. Make a lateral move first and then frontal.
	3. Store if the path is possible.

Assistance Received: none
********************************************************************* */
bool Board::isPathGood(int row, int col, int newRow, int newCol, bool correctPaths[]) {
	int frontal = newRow - row;
	int side = newCol - col;

	// Decrement the row and column values since the values gotten in parameter are user friendly.
	row = row - 1;
	col = col - 1;

	if (board[row][col]->isEmpty()) {
		return false;
	}
	
	// At this point, it is obvious that the frontal and side are going to be good.
	if (board[row][col]->getDice()->getTop() != abs(frontal) + abs(side)) {
		if (!isGodMode) {
			cout << "The dice cannot make that movement due to mismatch of distance" << endl;
		}
		isGodMode = false;
		return false;
	}

	int index = 0;

	// If it is the computer, then do the increments accordingly and check in each location
	// for the cells to be empty.
	int tempRow = row;
	int tempCol = col;

	// If frontal or side movement is not needed remove it as correct paths.
	if (abs(frontal) == 0) correctPaths[0] = false;
	if (abs(side) == 0) correctPaths[1] = false;

	// Loops frontal first and checks in each and every location if there are any dices.
	for (index = 1; index <= abs(frontal); index++) {
		int j = frontal < 0 ? -index : index;
		tempRow = row + j;

		// This is if its the main location, just ignore this step.
		if (tempRow + 1 == newRow && tempCol + 1 == newCol) continue;

		// If there is a die on the way, indicate that path as not possible.
		if (!board[tempRow][tempCol]->isEmpty()) correctPaths[0] = false;
	}

	// Make a 90 degree turn if needed and if frontal path is going correct until now.
	if (correctPaths[0] == true) {
		for (index = 1; index < abs(side); index++) {
			int j = side < 0 ? -index : index;
			tempCol = col+ j;
			if (!board[tempRow][tempCol]->isEmpty()) correctPaths[0] = false;
		}
	}

	// Reset temp row and columns.
	tempRow = row;
	tempCol = col;

	// Loops through lateral movement first and checks if there are any dices in each location.
	for (index = 1; index <= abs(side); index++) {
		int j = side < 0 ? -index : index;
		tempCol = col + j;

		// If its the main location, just ignore this step.
		if (tempRow + 1 == newRow && tempCol + 1 == newCol) continue;
		
		// If there is a dice on the way, indicate it as incorrect path.
		if (!board[tempRow][tempCol]->isEmpty()) correctPaths[1] = false;
	}

	// Make a 90 degree turn if needed and if frontal path is going correct until now.
	if (correctPaths[1] == true) {
		for (index = 1; index < abs(frontal); index++) {
			int j = frontal < 0 ? -index : index;
			tempRow = row + j;
			if (!board[tempRow][tempCol]->isEmpty()) correctPaths[1] = false;
		}
	}
		
	// Checks if both direction paths are incorrect. 
	if (!correctPaths[0] && !correctPaths[1]) {
		if (!isGodMode) {
			cout << "There are hindrances on the path" << endl;
		}
		isGodMode = false;
	}

	isGodMode = false;

	// Returns true if either direction is true.
	return correctPaths[0] || correctPaths[1];
}

/* *********************************************************************
Function Name: checkPathForAlgo
Purpose: To check the path for automated process of verification of path. It will 
	help to handle the error cases. Important thing here is that the parameters are computer
	friendly. So, indexes in the parameter starts from 0.

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.
	isGodMode, a boolean. It holds if the process is god mode.

Return Value: Returns true if the path from one location to another is true.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
// The parameters bring in the rows and cols as computer's index i.e. it starts from 0.
bool Board::checkPathForAlgo(int row, int col, int newRow, int newCol, bool isGodMode) {
	this->isGodMode = isGodMode;
	bool tempDir[2];
	tempDir[0] = true;
	tempDir[1] = true;

	return isPathGood(row + 1, col + 1, newRow + 1, newCol + 1, tempDir);
}

/* *********************************************************************
Function Name: moveFromAlgo
Purpose: To move dice from one location to another for automated process.
	Important thing is that the parameters are computer friendly. Indexes
	start from 0.

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.

Return Value: Returns the dice if any dices are eaten in the process.

Local Variables:
	tempDir[2], a boolean array. Holds the directions temporarily.

Algorithm: none.

Assistance Received: none
********************************************************************* */
Dice * Board::moveFromAlgo(int row, int col, int newRow, int newCol) {
	// Temporarily creates an array of directions to call the main board function.
	bool tempDir[2];
	tempDir[0] = true;
	tempDir[1] = true;
	char direction = 'f';

	// Checks if the path is good.
	isPathGood(row + 1, col + 1, newRow + 1, newCol + 1, tempDir);

	if (tempDir[0] == false) {
		direction = 'l';
	}

	// Returns the move native function.
	return move(row + 1, col + 1, newRow + 1, newCol + 1, direction);
}

/* *********************************************************************
Function Name: isLegalAlgo
Purpose: To check if the path is legal. This is for automated process.
	Important info is that the parameters are computer friendly. Indexes start from 0.

Parameters:
	row, an integer. It holds the row of the current dice.
	column,an integer. It holds the column of the current dice.
	newRow,an integer. It holds the new row to be moved to.
	newCol,an integer. It holds the new column to be moved to.

Return Value: Returns true if the move from one location to another is legal.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool Board::isLegalAlgo(int row, int column, int newRow, int newCol, bool isComputer) {
	isGodMode = true;

	return isLegal(row + 1, column + 1, newRow + 1, newCol + 1, isComputer);
}

