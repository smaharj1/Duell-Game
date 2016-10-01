#include "computer.h"



computer::computer()
{
}

computer::computer(int keys[], int size) {
	int top = 0, right = 0, front = 0;
	int mid = size / 2;
	for (int index = 0; index < size; index++) {
		top = keys[index];
		right = 3;
		front = Dice::computeFrontFace(top, right);

		// here, right is technically front. We are considering it right to find an actual right.
		if (index == mid) {
			computerDices[index] = new Dice(true, 1, 1, 1);
		}
		else {
			computerDices[index] = new Dice(true, top, right, 7 - front);
		}

	}
}

computer::computer(Board * board) {
	Dice * tmp;
	int diceIndex = 0;
	for (int row = 0; row < board->getTotalRows(); row++) {
		for (int col = 0; col < board->getTotalColumns(); col++) {
			tmp = board->getCell(row, col)->getDice();
			if (tmp != NULL) {
				if (!tmp->isPlayerComputer()) {
					computerDices[diceIndex] = tmp;
					diceIndex++;
				}
			}
		}
	}

	// This nullifies the remaining dice locations. It means the dices are eaten.
	for (int i = diceIndex; i < 9; i++) {
		computerDices[i] = NULL;
	}
}

computer::~computer()
{
}

Dice * computer::play(Board * board) {
	// Defend the king first.
	if (algorithm::goDefence(board, true)) {

	}
	

	// If it is defended, see if you can attack.

	// If nothing is attackable, do best first search.


	cout << "computer's turn to play !!!" << endl;
	return NULL;
}