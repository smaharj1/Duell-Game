#include "human.h"



human::human()
{
	
}

human::human(int keys[], int size)
{
	int top = 0, right = 0, front = 0;
	int mid = size / 2;
	for (int index = 0; index < size; index++) {
		top = keys[index];
		right = 3;
		front = Dice::computeFrontFace(top, right);

		// here, right is technically front. We are considering it right to find an actual right.
		if (index == mid) {
			humanDices[index] = new Dice(false, 1, 1, 1);
		}
		else {
			humanDices[index] = new Dice(false, top, right, 7 - front);
		}

	}
}

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


human::~human()
{

}

Dice * human::play(Board * board) {
	row = -1; column = -1; newRow = -1; newCol = -1;
	char direction;

	cout << "It is your turn. Please make a move " << endl;
	// Asks for user's move
	do {
		char r, c, newR, newC;

		do {
			cout << "What is your move? Please give coordinates from 1 1 to 8 9 :: ";
			cin >> r >> c;

			cout << "Enter the preferred destination 1 1 to 8 9 :: ";
			cin >> newR >> newC;
		} while (!validValues(r, c, newR, newC));

		row = r - '0';
		column = c - '0';
		newRow = newR - '0';
		newCol = newC - '0';
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
			cout << "Invalid character entered" << endl;
		}
	} while (direction != 'f' && direction != 'l');


	// If it returns true while moving, it means that the player moving won other player's dice.
	Dice * returnedDice = board->move(row, column, newRow, newCol, direction);

	return returnedDice;
}

bool human::validValues(char row, char col, char newRow, char newCol) {
	bool res = isdigit(row) && isdigit(col) && isdigit(newRow) && isdigit(newCol);
	if (!res) {
		cout << "Some of the values entered are not numbers" << endl;
	}
	return res;
}