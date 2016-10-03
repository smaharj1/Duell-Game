/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
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

	determineTurn();

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

void game::determineTurn() {
	srand(time(NULL));
	bool humanTurn = true;
	char userInput;
	int humanDie = 0; int computerDie = 0;

	while (humanDie == computerDie) {
		cout << "Please enter any key to toss a die: ";
		cin >> userInput;

		humanDie = rollDie();
		cout << "You rolled " << humanDie << endl;

		computerDie = rollDie();
		cout << "Computer rolled " << computerDie << endl;	

		if (humanDie == computerDie) {
			cout << "It is a draw. Repeat the roll." << endl;
		}
	}

	if (computerDie > humanDie) {
		cout << "Computer goes first!" << endl;
		isComputersTurn = true;
	}
	else {
		cout << "You go first!" << endl;
		isComputersTurn = false;
	}

}

int game::rollDie() {
	return rand() % 6 + 1;
}

bool game::isComputerWinner() {

	//TODO: needs changes
	return computerWin;
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

			Dice * returnedDice = bot->play(board);

			if (returnedDice != NULL) {
				// Here, the dice that was lost is returned.
				if (returnedDice->isPlayerKing()) {
					isDone = true;
					computerWin = true;
					cout << "####-----------------####--------------------####" << endl;
					cout << "Computer WON!!!!!!!!!!!!" << endl;
					cout << "Sorry! Better be smart first" << endl << endl;
				}
				else {
					returnedDice->setKilled();
				}
			}

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
