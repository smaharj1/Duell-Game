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

}


game::~game()
{
}

bool game::isComputerWinner() {

	//TODO: needs changes
	return false;
}

void game::startGame() {
	int row, column, frontal, side;
	while (!isDone) {
		row = -1, column = -1, frontal = -1, side = -1;

		// Prints the board first.
		boardView.printBoard();

		// Randomly assigns the turn of the player. Currently, its just user first.
		if (!isComputersTurn) {
			// Asks for user's move
			do {
				cout << "What is your move? Please give coordinates from 1 1 to 8 9 :: ";
				cin >> row >> column;
							
				cout << endl << "Your frontal movement (+ve if front, -ve if backward):: ";
				cin >> frontal;

				cout << endl << "Your side movement (+ve if right, -ve if left):: ";
				cin >> side;
			} while (!isMoveLegal(row, column, frontal, side, false));
			

			
		}

		// Moves it according to user's choice
	}
}

bool game::isMoveLegal(int row, int col, int frontal, int side, bool isComputer) {
	return board->isLegal(row, col, frontal, side, isComputer);
}