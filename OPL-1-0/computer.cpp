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

	// First, check if the bot can win.
	if (algo->canWin()) {
		suggestedMove = algo->getSuggestedMoves();
		suggestedLocation = algo->getSuggestedLocation();

		printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
		
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// Defend the king first.
	if (algo->kingInThreat()) {
		if (algo->canEatThreat()) {
			cout << "You tried to eat my king huh? Smart!" << endl << "Just kidding! This is for you, love! Rest In Peace!" << endl << endl;
			suggestedMove = algo->getSuggestedMoves();
			suggestedLocation = algo->getSuggestedLocation();
			
			printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
			cout << "Mess is cleaned up" << endl;
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
		else if (algo->canMoveKing(true)) {
			// Try to move the king to escape.
			suggestedMove = algo->getSuggestedMoves();
			suggestedLocation = algo->getSuggestedLocation();
			printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
	}

	// If the king does not have any threat, try to eat other players
	if (algo->canEatOpponent()) {
		suggestedMove = algo->getSuggestedMoves();
		suggestedLocation = algo->getSuggestedLocation();
		printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
		cout << "-------How do you like them apples?---------" << endl;
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// If nothing is attackable, move the dice closest to opponent where opponent can't eat.
	if (algo->safeOffense()) {
		suggestedMove = algo->getSuggestedMoves();
		suggestedLocation = algo->getSuggestedLocation();
		printMove(8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, true);
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// Pick random location and move it (NO CHOICE Stage).

	return NULL;
}