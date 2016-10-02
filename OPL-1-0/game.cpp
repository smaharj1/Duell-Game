#include "game.h"

/*
	Initiates the game by assigning the players and the board
*/
game::game()
{
	const int SIZE = 9;
	int given[SIZE] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };
	// Assign players here
	humanP = new human(given, SIZE);
	bot = new computer(given, SIZE);

	board = new Board(humanP->getDices(), bot->getDices(), SIZE);

	boardView.setBoard(board);

	isComputersTurn = false;
	isDone = false;
	computerWin = true;

}

game::game(Board * tempBoard, bool computersTurn) {
	board = tempBoard;
	isComputersTurn = computersTurn;

	boardView.setBoard(board);

	humanP = new human(board);
	bot = new computer(board);

	isDone = false;
	computerWin = true;
	
}

game::~game()
{
}

bool game::isComputerWinner() {

	//TODO: needs changes
	return false;
}

// this will update if the game is finished or it is just saved.
bool game::startGame() {

	while (!isDone) {

		// Prints the board first.
		boardView.printBoard();

		/*
		// Prompt the user if they want to keep playing
		cout << "Do you want to keep playing or save the game? (S for save/ any for keep playing):: ";
		cin >> userInput;

		if (userInput == 'S' || userInput == 's') {
			return false;
		}
		*/

		// Randomly assigns the turn of the player. Currently, its just user first.
		if (!isComputersTurn) {

			Dice * returnedDice = humanP->play(board);

			if (returnedDice != NULL) {
				// Here, the dice that was lost is returned.
				if (returnedDice->isPlayerKing()) {
					isDone = true;
					computerWin = false;
					cout << "####-----------------####--------------------####" << endl;
					cout << "YOU WON!!!!!!!!!!!!" << endl;
					cout << "Go brag about it! You won the computer!" << endl << endl;
				}
				else {
					returnedDice->setKilled();
				}
			}

		}
		else {
			cout << "It is computer's turn." << endl;

			bot->play(board);
		}

		
		// TODO: change the player's turn
		isComputersTurn = !isComputersTurn;

	}

	return true;
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
