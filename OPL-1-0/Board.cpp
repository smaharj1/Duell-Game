#include "Board.h"



Board::Board()
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			Dice * d;
			if (i == 0) {
				d = new Dice("C51");
				board[i][j] = new Cell(d);
			}
			else if (i == ROWS - 1) {
				d = new Dice("H12");
				board[i][j] = new Cell(d);
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

bool Board::move(int row, int column, int frontal, int side) {
	// Holds if the player is computer or human.
	bool isComputer = board[row-1][column-1]->getDice()->isPlayerComputer();

	// If the cell in the board is empty, return that it is empty.
	if (board[row - 1][column - 1]->isEmpty()) {
		cout << "The selection is empty." << endl;
		return false;
	}
	
	// Coordinates that hold the new X and Y positions according to the players
	int newX = -1;
	int newY = -1;
	
	// If it is computer's move, then arrange the coordinates accordingly.
	if (isComputer) {
		// Check if it is outside of range of the board.
		if (frontal + row > ROW_HIGH_LIMIT || frontal + row < ROW_LOW_LIMIT ||
			column -side > 9 ||  column -side < 1) {
			cout << "Invalid move. It is outside the board" << endl;
			return false;
		}

		// Calculates the new position.
		newX = row - 1 + frontal;
		newY = column - 1 - side;

		// If the new location is not empty, and it is of the same player, return error.
		if (!board[newX][newY]->isEmpty() && board[newX][newY]->getDice()->isPlayerComputer()) {
			cout << "Illegal move. You tried replacing your own player" << endl;
			return false;
		}
	}
	else {
		// If it is human, find its new coordinates.
		if (row - frontal > ROW_HIGH_LIMIT || row - frontal < ROW_LOW_LIMIT ||
			column + side > COLUMN_HIGH_LIMIT || column + side < COLUMN_LOW_LIMIT) {
			cout << "Invalid move. It is outside the board" << endl;
			return false;
		}
		// Calculates the new position.
		newX = row - 1 - frontal;
		newY = column - 1 + side;

		// If the new location is not empty, and it is of the same player, return error.
		if (!board[newX][newY]->isEmpty() && !board[newX][newY]->getDice()->isPlayerComputer()) {
			cout << "Illegal move. You tried replacing your own player" << endl;
			return false;
		}
	}

	// Checks if the dice is rolled forward or backward and assigns the rolling accordingly.
	for (int i = 0; i < abs(frontal); i++) {
		frontal >0 ? board[row - 1][column - 1]->getDice()->moveForward() :
			board[row - 1][column - 1]->getDice()->moveBackward();
	}

	// Checks if the dice is rolled right or left and assigns the rolling accordingly.
	for (int i = 0; i < abs(side); i++) {
		side > 0 ? board[row - 1][column - 1]->getDice()->moveRight() :
			board[row - 1][column - 1]->getDice()->moveLeft();
	}

	// Adds the dice to the Cell and removes the dice from previous location.
	board[newX][newY]->addDice(board[row - 1][column - 1]->getDice());
	board[row - 1][column - 1]->removeDice();

	return true;
}


bool Board::isLegal(int row, int column, int frontal, int side, bool playerIsComputer) {
	// Holds if the player is computer or human.
	bool isComputer = board[row - 1][column - 1]->getDice()->isPlayerComputer();

	if (playerIsComputer != isComputer) {
		cout << "You cannot move other players dice." << endl;
		return false;
	}
	// If the cell in the board is empty, return that it is empty.
	if (board[row - 1][column - 1]->isEmpty()) {
		cout << "The selection is empty." << endl;
		return false;
	}

	// Coordinates that hold the new X and Y positions according to the players
	int newX = -1;
	int newY = -1;

	// If it is computer's move, then arrange the coordinates accordingly.
	if (isComputer) {
		// Check if it is outside of range of the board.
		if (frontal + row > ROW_HIGH_LIMIT || frontal + row < ROW_LOW_LIMIT ||
			column - side > 9 || column - side < 1) {
			cout << "Invalid move. It is outside the board" << endl;
			return false;
		}

		// Calculates the new position.
		newX = row - 1 + frontal;
		newY = column - 1 - side;

		// If the new location is not empty, and it is of the same player, return error.
		if (!board[newX][newY]->isEmpty() && board[newX][newY]->getDice()->isPlayerComputer()) {
			cout << "Illegal move. You tried replacing your own player" << endl;
			return false;
		}
	}
	else {
		// If it is human, find its new coordinates.
		if (row - frontal > ROW_HIGH_LIMIT || row - frontal < ROW_LOW_LIMIT ||
			column + side > COLUMN_HIGH_LIMIT || column + side < COLUMN_LOW_LIMIT) {
			cout << "Invalid move. It is outside the board" << endl;
			return false;
		}
		// Calculates the new position.
		newX = row - 1 - frontal;
		newY = column - 1 + side;

		// If the new location is not empty, and it is of the same player, return error.
		if (!board[newX][newY]->isEmpty() && !board[newX][newY]->getDice()->isPlayerComputer()) {
			cout << "Illegal move. You tried replacing your own player" << endl;
			return false;
		}
	}

	return isPathGood(row-1, column-1, newX, newY) ? true : false;
}

bool Board::isPathGood(int row, int col, int newRow, int newCol) {
	return true;
}