/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
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

void human::askForHelp(Board * board) {
	algorithm algo(board, false);

	treeNode * suggestedMove;
	location * suggestedLocation;

	// First, check if the bot can win.
	if (algo.canWin()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();

		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanWin);
		return;
	}

	// Defend the king first.
	if (algo.kingInThreat()) {
		if (algo.canEatThreat()) {
			
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatKingsThreat);
			return;
			
		}
		else if (algo.canMoveKing()) {
			// Try to move the king to escape.
			suggestedMove = algo.getSuggestedMoves();
			suggestedLocation = algo.getSuggestedLocation();
			printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::MoveKing);
			return;
		}
	}

	// If the king does not have any threat, try to eat other players
	if (algo.canEatOpponent()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::CanEatOpponent);
		return;
	}

	// If nothing is attackable, move the dice closest to opponent where opponent can't eat.
	if (algo.safeOffense()) {
		suggestedMove = algo.getSuggestedMoves();
		suggestedLocation = algo.getSuggestedLocation();
		printMove(suggestedMove->getDice(), 8 - suggestedMove->getRow(), suggestedMove->getColumn() + 1, 8 - suggestedLocation->getRow(), suggestedLocation->getColumn() + 1, GameCondition::PlaySafe);
		return;
	}

}

char askIfHelpNeeded() {
	char userInput;
	cout << "Would you like some help (Y for yes, anything else for No)? ";
	cin >> userInput;

	return tolower(userInput);
}

Dice * human::play(Board * board) {
	row = -1; column = -1; newRow = -1; newCol = -1;
	char direction;

	cout << "It is your turn. Please make a move " << endl;
	board->setGodMode(false);

	// Asks for user's move
	do {
		char r, c, newR, newC;

		char userInput = askIfHelpNeeded();
		if (userInput == 'y') {
			askForHelp(board);
		}

		do {
			cout << "Enter your move? Please give coordinates from 1 1 to 8 9 :: ";
			cin >> r >> c;

			cout << "Enter the preferred destination from 1 1 to 8 9 :: ";
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
			cout << "Invalid character entered. Please enter it again" << endl;
		}
	} while (direction != 'f' && direction != 'l');


	// If it returns true while moving, it means that the player moving won other player's dice.
	Dice * returnedDice = board->move(row, column, newRow, newCol, direction);

	printActivity(9-row, column, 9-newRow, newCol, false, direction);

	return returnedDice;
}

bool human::validValues(char row, char col, char newRow, char newCol) {
	bool res = isdigit(row) && isdigit(col) && isdigit(newRow) && isdigit(newCol);
	if (!res) {
		cout << "Some of the values entered are not numbers" << endl;
	}
	return res;
}


void human::printMove(Dice * givenDice, int row, int column, int newRow, int newCol, GameCondition condition) {
	cout << "You can move " << givenDice->getValue() << " at (" << row << "," << column << ") to (" << newRow << "," << newCol << ") roll because ";

	switch (condition) {
	case CanWin:
		cout << " it could make you win the game." << endl;
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
}