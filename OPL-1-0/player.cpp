#include "player.h"



player::player()
{
	totalWins = 0;
}


player::~player()
{
}

int player::getColumn() {
	return column;
}

int player::getNewCol() {
	return newCol;
}

int player::getRow() {
	return row;
}

int player::getNewRow() {
	return newRow;
}

int player::isMoveInBound(int r, int c, int newR, int newC) {
	if (row < ROW_LOW_LIMIT || newRow < ROW_LOW_LIMIT || column < COLUMN_LOW_LIMIT || newCol < COLUMN_LOW_LIMIT ||
		row > ROW_HIGH_LIMIT || newRow > ROW_HIGH_LIMIT || column > COLUMN_HIGH_LIMIT || newCol > COLUMN_HIGH_LIMIT) {
		cout << "Coordinates are out of bound. Please enter again." << endl << endl;
		return false;
	}

	return true;
}

void player::printMove(int row, int column, int newRow, int newCol, bool isComputer, int direction) {
	cout << "--------------------------------------------------------------" << endl;
	if (isComputer) {
		cout << "Computer ";
	}
	else {
		cout << "You ";
	}

	cout << "moved the dice from (" << row << "," << column << ") to (" << newRow << "," << newCol << ") taking ";

	if (direction == 'f') cout << "frontal move first";
	else cout << "lateral move first" << endl;
}

void player::printMove(int row, int column, int newRow, int newCol, bool isComputer) {
	cout << "--------------------------------------------------------------" << endl;
	if (isComputer) {
		cout << "Computer ";
	}
	else {
		cout << "You ";
	}

	cout << "moved the dice from (" << row << "," << column << ") to (" << newRow << "," << newCol << ")" << endl;
}