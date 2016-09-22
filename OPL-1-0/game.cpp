#include "game.h"

/*
	Initiates the game by assigning the players and the board
*/
game::game()
{
	// Assign players here

	board = new Board();

	boardView.setBoard(board);

	isComputersTurn = false;
	isDone = false;
	computerWin = true;

	humanP = new human();
	bot = new computer();

}


game::~game()
{
}

bool game::isComputerWinner() {

	//TODO: needs changes
	return false;
}

void game::startGame() {
	int row, column, newRow, newCol;
	while (!isDone) {
		//row = -1, column = -1, newRow = -1, newCol = -1;

		// Prints the board first.
		boardView.printBoard();

		bool paths[2];

		// Randomly assigns the turn of the player. Currently, its just user first.
		if (!isComputersTurn) {
			//cout << "It is your turn. Please make a move " << endl;
			// Asks for user's move
			do {
				humanP->play();
				paths[0] = true;
				paths[1] = true;
			} while (isMoveLegal(humanP->getRow(), humanP->getColumn(), humanP->getNewRow(), humanP->getNewCol(), false) == false ||
				isPathLegal(humanP->getRow(), humanP->getColumn(), humanP->getNewRow(), humanP->getNewCol(), paths) == false);
			
			

			// If it returns true while moving, it means that the player moving won other player's dice.
			Dice * returnedDice = board->move(humanP->getRow(), humanP->getColumn(), humanP->getNewRow(), humanP->getNewCol());

			if (returnedDice != NULL) {
				// Here, the dice that was lost is returned.
				if (returnedDice->isPlayerKing()) {
					isDone = true;
					computerWin = false;
				}
			}

		}
		else {
			cout << "It is computer's turn." << endl;

			bot->play();

			/*
			// Asks for user's move
			do {
				cout << "What is your move? Please give coordinates from 1 1 to 8 9 :: ";
				cin >> row >> column;

				cout << "Enter the preferred destination 1 1 to 8 9 :: ";
				cin >> newRow >> newCol;

				// convert user given input to array compatible input 
				row = MAX_ROW - row;
				newRow = MAX_ROW - newRow;
				paths[0] = true;
				paths[1] = true;
			} while (isMoveLegal(row, column, newRow, newCol, true) == false ||
				isPathLegal(row, column, newRow, newCol, paths) == false);

			// If it returns true while moving, it means that the player moving won other player's dice.
			Dice * returnedDice = board->move(row, column, newRow, newCol);
			if (returnedDice != NULL) {
				// Here, the dice that was lost is returned.
				if (returnedDice->isPlayerKing()) {
					isDone = true;
					computerWin = false;
				}
			}

			*/

		}

		printMove(MAX_ROW-humanP->getRow(), humanP->getColumn(), MAX_ROW - humanP->getNewRow(), humanP->getNewCol(), isComputersTurn);
		// TODO: change the player's turn
		isComputersTurn = !isComputersTurn;

		// Moves it according to user's choice
	}
}

bool game::isMoveLegal(int row, int col, int newRow, int newCol, bool isComputer) {
	return board->isLegal(row, col, newRow, newCol, isComputer);
}

bool game::isPathLegal(int row, int col, int newRow, int newCol, bool correctPaths[]) {
	return board->isPathGood(row, col, newRow, newCol, correctPaths);
}

void game::printMove(int row, int col, int newRow, int newCol, bool isComputer) {
	if (isComputer) {
		cout << endl << "Computer ";
	}
	else {
		cout << endl << "You ";
	}

	cout << "moved the dice from " << row << " " << col << " to " << newRow << " " << newCol << endl << endl;
}