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
				d = new Dice("H65");
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