/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
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

void computer::printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition) {
	cout << "The computer picked " << givenDice->getValue() << " because ";

	switch (condition) {
	case CanWin:
		cout << " it could make computer win the game." << endl;
		break;
	case CanEatKingsThreat:
		cout << " it removed the threat from the king by eating it." << endl;
		break;
	case CanEatOpponent:
		cout << " it ate the opponent's dice." << endl;
		break;
	case MoveKing:
		cout << " the king was going to die in next step and there was no way of protection." << endl;
		break;
	case PlaySafe:
		cout << " it is best to play safe. No one can eat the dice in this new location" << endl;
		break;
	}

	int frontal = newRow - row;
	if (frontal < 0) {
		cout << "It moved frontal by " << abs(frontal) << " because it led to the current situation. " << endl;
	}
	else if (frontal >0) {
		cout << "It moved back by " << abs(frontal) << " because it led to the current situation. " << endl;
	}

	int side = newCol - column;
	if (side < 0) {
		cout << "It moved left by " << abs(side) << " because it led to the current situation. " << endl;
	}
	else if (side >0) {
		cout << "It moved right by " << abs(side) << " because it led to the current situation. " << endl;
	}

}


Dice * computer::play(Board * board) {
	algorithm algo(board, true);
	treeNode * suggestedMove;
	location * suggestedLocation;

	// First, check if the bot can win.
	if (algo.canWin()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();

		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanWin);
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// Defend the king first.
	if (algo.isKingInThreat()) {
		if (algo.canEatThreat()) {
			cout << "You tried to eat my king huh? Smart!" << endl << "Just kidding! This is for you, love! Rest In Peace!" << endl << endl;
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatKingsThreat);
			cout << "Mess is cleaned up" << endl;
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
		else if (algo.canMoveKing()) {
			// Try to move the king to escape.
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::MoveKing);
			Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
			return d;
		}
	}

	// If the king does not have any threat, try to eat other players
	if (algo.canEatOpponent()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		cout << "-------How do you like them apples?---------" << endl;
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatOpponent);
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// If nothing is attackable, move the dice closest to opponent where opponent can't eat.
	if (algo.safeOffense()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::PlaySafe);
		Dice * d = board->moveFromAlgo(suggestedMove->getRow(), suggestedMove->getColumn(), suggestedLocation->getRow(), suggestedLocation->getColumn());
		return d;
	}

	// Pick random location and move it (NO CHOICE Stage).

	return NULL;
}