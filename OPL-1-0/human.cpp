#include "human.h"



human::human()
{
	
}


human::~human()
{

}

void human::play(Board * board) {
	row = -1; column = -1; newRow = -1; newCol = -1;
	char direction;

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
	} while (!isMoveInBound(row, column, newRow, newCol) ||
		board->isLegal(row, column, newRow, newCol, false) == false ||
		board->isPathGood(row, column, newRow, newCol, paths) == false);

	// At this point, one of the path is valid. So, just check with user if they want any prefered direction.
	do {
		cout << "Do you want to move FRONTAL or LATERAL first? (F/L) :: ";
		cin >> direction;

		direction = tolower(direction);
		// path[0] is frontal movement
		if ((direction == 'f')) {
			if (paths[0] == true) {
				cout << "Moving the dice frontally first..." << endl;
			}
			else {
				cout << "Dice cannot make frontal move first because of the distractions... Going lateral..." << endl;
			}
		}
		else if (direction == 'l') {
			if (paths[1] == true) {
				cout << "Moving the dice laterally first..." << endl;
			}
			else {
				cout << "Dice cannot make lateral move first because of the distractions... Going frontal..." << endl;
			}
		}
		else {
			cout << "Invalid character entered" << endl;
		}
	} while (direction != 'f' && direction != 'l');


	// If it returns true while moving, it means that the player moving won other player's dice.
	//Dice * returnedDice = board->move(row, column, newRow, newCol);

}