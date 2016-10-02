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
	algorithm * algo = new algorithm(board, true);
	treeNode * suggestedMove;
	location * suggestedLocation;

	// Defend the king first.
	if (algo->kingInThreat(board)) {
		if (algo->canEatThreat(board)) {
			cout << "You tried to eat my king huh? Smart!" << endl << "Just kidding! This is for you, love! Rest In Peace!" << endl << endl;
			suggestedMove = algo->getSuggestedMoves();
			suggestedLocation = algo->getSuggestedLocation();
			
			printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
			cout << "Mess is cleaned up" << endl;
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
		else if (algo->canMoveKing(board, true)) {
			// Try to move the king to escape.
			suggestedMove = algo->getSuggestedMoves();
			suggestedLocation = algo->getSuggestedLocation();
			printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
	}

	// If there is no threat for the king, see if you can attack and eat other team.

	// If nothing is attackable, do best first search.


	return NULL;
}