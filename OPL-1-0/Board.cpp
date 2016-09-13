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


void Board::printBoard() {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			if (board[i][j]->getDice() != NULL) {
				cout << board[i][j]->getDice()->getValue() << "  ";
			}
			else {
				cout << "  0  ";
			}
		}
		cout << endl;
	}
}

bool Board::move(int x, int y, int frontal, int side) {
	if (board[x - 1][y - 1]->isEmpty()) {
		return false;
	}

	// check for over or under the limit of row and column.

	for (int i = 0; i < frontal; i++) {
		board[x - 1][y - 1]->getDice()->moveForward();
	}

	for (int i = 0; i < side; i++) {
		board[x - 1][y - 1]->getDice()->moveRight();
	}

	int newX = x - 1 - frontal;
	int newY = y - 1 - side;

	board[newX][newY]->addDice(board[x - 1][y - 1]->getDice());
	board[x - 1][y - 1]->removeDice();
}