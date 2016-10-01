#include "Board.h"



Board::Board()
{
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
}

Board::Board(Dice ** human, Dice ** bot, int size) {
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
}

Board::~Board()
{
}

void Board::setBoard(string tempBoard[][9]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (tempBoard[i][j] == "0") {
				board[i][j] = new Cell();
			}
			else {
				board[i][j] = new Cell(new Dice(tempBoard[i][j]));
			}
		}
	}
}

Dice * Board::move(int row, int column, int newRow, int newCol) {
	Dice * diceAte = NULL;

	// Holds if the player is computer or human.
	bool isComputer = board[row-1][column-1]->getDice()->isPlayerComputer();

	// If the cell in the board is empty, return that it is empty.
	if (board[row - 1][column - 1]->isEmpty()) {
		cout << "The selection is empty." << endl;
		return false;
	}

	int frontal = newRow - row;
	int side = newCol - column;
	
	if (!isComputer) {
		// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
		for (int i = 0; i < abs(frontal); i++) {
			frontal < 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
				board[row - 1][column - 1]->getDice()->moveBackward();

			//cout << board[row - 1][column - 1]->getDice()->getValue() << endl;
		}

		// Checks if the dice is rolled right or left and assigns the rolling accordingly.
		for (int i = 0; i < abs(side); i++) {
			side > 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
				board[row - 1][column - 1]->getDice()->moveLeft();

			//cout << board[row - 1][column - 1]->getDice()->getValue() << endl;
		}
	}
	else {
		// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
		for (int i = 0; i < abs(frontal); i++) {
			frontal > 0 ? board[row - 1][column - 1]->getDice()->moveForward() :
				board[row - 1][column - 1]->getDice()->moveBackward();

			//cout << board[row - 1][column - 1]->getDice()->getValue() << endl;
		}

		// Checks if the dice is rolled right or left and assigns the rolling accordingly.
		for (int i = 0; i < abs(side); i++) {
			side < 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
				board[row - 1][column - 1]->getDice()->moveLeft();

			//cout << board[row - 1][column - 1]->getDice()->getValue() << endl;
		}
	}

	// Adds the dice to the Cell and removes the dice from previous location.

	if (!board[newRow - 1][newCol - 1]->isEmpty()) {
		cout << "Dice is eaten!" << endl << endl;
		diceAte = board[newRow - 1][newCol - 1]->getDice();
		board[newRow - 1][newCol - 1]->removeDice();
	}
	board[newRow-1][newCol-1]->addDice(board[row - 1][column - 1]->getDice());
	board[row - 1][column - 1]->removeDice();

	return diceAte;
}


bool Board::isLegal(int row, int column, int newRow, int newCol, bool playerIsComputer) {

	// If the cell in the board is empty, return that it is empty.
	if (board[row - 1][column - 1]->isEmpty()) {
		cout << "The selection is empty." << endl;
		return false;
	}

	// Holds if the player is computer or human.
	bool isComputer = board[row - 1][column - 1]->getDice()->isPlayerComputer();

	if (playerIsComputer != isComputer) {
		cout << "You cannot move other players dice." << endl;
		return false;
	}

	if (!board[newRow - 1][newCol - 1]->isEmpty()) {
		if ((board[row - 1][column - 1]->getDice()->isPlayerComputer() && board[newRow - 1][newCol - 1]->getDice()->isPlayerComputer()) ||
			!board[row - 1][column - 1]->getDice()->isPlayerComputer() && !board[newRow - 1][newCol - 1]->getDice()->isPlayerComputer()) {
			cout << "You cannot replace your own player" << endl;
			return false;
		}
	}

	return true;
}


bool Board::isPathGood(int row, int col, int newRow, int newCol, bool correctPaths[]) {
	int frontal = newRow - row;
	int side = newCol - col;

	row = row - 1;
	col = col - 1;

	if (board[row][col]->isEmpty()) {
		return false;
	}

	// At this point, it is obvious that the frontal and side are going to be good.
	if (board[row][col]->getDice()->getTop() != abs(frontal) + abs(side)) {
		cout << "The dice cannot make that movement due to mismatch of distance" << endl;
		return false;
	}

	// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
	

	// Checks if the dice is rolled right or left and assigns the rolling accordingly.

	int i = 0;

	// If it is the computer, then do the increments accordingly and check in each location
	// for the cells to be empty.
	int tempRow = row;
	int tempCol = col;

	for (i = 1; i <= abs(frontal); i++) {
		int j = frontal < 0 ? -i : i;
		tempRow = row + j;
		if (!board[tempRow][tempCol]->isEmpty()) correctPaths[0] = false;
	}

	if (correctPaths[0] == true) {
		for (i = 1; i < abs(side); i++) {
			int j = side < 0 ? -i : i;
			tempCol = col+ j;
			if (!board[tempRow][tempCol]->isEmpty()) correctPaths[0] = false;
		}
	}

	tempRow = row;
	tempCol = col;

	for (i = 1; i <= abs(side); i++) {
		int j = side < 0 ? -i : i;
		tempCol = col + j;
		if (!board[tempRow][tempCol]->isEmpty()) correctPaths[1] = false;
	}
	if (correctPaths[1] == true) {
		for (i = 1; i < abs(frontal); i++) {
			int j = frontal < 0 ? -i : i;
			tempRow = row + j;
			if (!board[tempRow][tempCol]->isEmpty()) correctPaths[1] = false;
		}
	}
		
	if (!correctPaths[0] && !correctPaths[1]) {
		cout << "There are hindrances on the path" << endl;
	}
	return correctPaths[0] || correctPaths[1];
}