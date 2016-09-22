#include "human.h"



human::human()
{
	
}


human::~human()
{

}

void human::play() {
	row = -1; column = -1; newRow = -1; newCol = -1;

	cout << "It is your turn. Please make a move " << endl;
	// Asks for user's move
	do {
		cout << "What is your move? Please give coordinates from 1 1 to 8 9 :: ";
		cin >> row >> column;

		cout << "Enter the preferred destination 1 1 to 8 9 :: ";
		cin >> newRow >> newCol;

		// convert user given input to array compatible input 
		row = 9 - row;
		newRow = 9 - newRow;
		paths[0] = true;
		paths[1] = true;
	} while (!isMoveInBound(row, column, newRow, newCol));
}