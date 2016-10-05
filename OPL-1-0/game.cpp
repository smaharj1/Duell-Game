/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "game.h"

/* *********************************************************************
Function Name: game
Purpose: Default Constructor to start a new game.

Parameters: none.

Return Value: none.

Local Variables: 
	given[], an array. It holds the initial values to start a new game.

Algorithm: none.

Assistance Received: none
********************************************************************* */
game::game()
{
	const int SIZE = 9;
	int given[SIZE] = { 5, 1, 2, 6, 1, 6, 2, 1, 5 };

	// Assign players here
	humanP = new human(given, SIZE);
	bot = new computer(given, SIZE);

	// Starts a new board with the player dices as given.
	board = new Board(humanP->getDices(), bot->getDices());

	// Sets the board.
	boardView.setBoard(board);

	// Determines whose turn it is through a die game.
	determineTurn();

	// Initializes game states.
	isDone = false;
	computerWin = true;
}

/* *********************************************************************
Function Name: game
Purpose: Constructor for opening a game from text file

Parameters: 
	tempBoard, a pointer. It holds the pointer to the board.
	computersTurn, a boolean. It holds if it is computer's turn.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
game::game(Board * tempBoard, bool computersTurn) {
	// Sets the board.
	board = tempBoard;

	// Sets the turn.
	isComputersTurn = computersTurn;

	// Sets the board view.
	boardView.setBoard(board);

	// Sets the human and computer players.
	humanP = new human(board);
	bot = new computer(board);

	// Sets the game conditions.
	isDone = false;
	computerWin = true;
	
}

/* *********************************************************************
Function Name: game
Purpose: Destructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
game::~game()
{
	delete board;
	delete humanP;
	delete bot;
	
}

/* *********************************************************************
Function Name: determineTurn
Purpose: To determine the first player to play the game. It starts a mini
	die rolling game where the one with higher score in the roll gets to play
	first. It is determined randomly.

Parameters: none.

Return Value: none.

Local Variables: 
	userInput, a character. It holds the user's input.
	humanDie, an integer. It holds the value of die rolled by the user.
	computerDie, an integer. It holds the value of the die rolled by the computer.

Algorithm: 
	1. Roll human die.
	2. Roll computer die.
	3. Whoever's die is higher, its their turn.
	4. If dices are equal, repeat the process.

Assistance Received: none
********************************************************************* */
void game::determineTurn() {
	srand(time(NULL));
	
	char userInput;
	int humanDie = 0; int computerDie = 0;

	// Keep rolling the dies until its draw.
	while (humanDie == computerDie) {

		do {
			// Ask user to toss the die.
			cout << "Please enter R any key to toss a die: ";
			cin >> userInput;
			userInput = tolower(userInput);
		} while (userInput != 'r');

		humanDie = rollDie();
		cout << "You rolled " << humanDie << endl;

		computerDie = rollDie();
		cout << "Computer rolled " << computerDie << endl;	

		if (humanDie == computerDie) {
			cout << "It is a draw. Repeat the roll." << endl;
		}
	}

	// Assign the turn according to the die roll result.
	if (computerDie > humanDie) {
		cout << "Computer goes first!" << endl;
		isComputersTurn = true;
	}
	else {
		cout << "You go first!" << endl;
		isComputersTurn = false;
	}
}

/* *********************************************************************
Function Name: rollDie
Purpose: To roll the die.

Parameters: none.

Return Value: Returns the die value rolled.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
int game::rollDie() {
	return rand() % 6 + 1;
}

/* *********************************************************************
Function Name: isComputerWinner
Purpose: To check if computer is the winner.

Parameters: none.

Return Value: Returns true if computer is the winner.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
bool game::isComputerWinner() {

	//TODO: needs changes
	return computerWin;
}

/* *********************************************************************
Function Name: startGame
Purpose: To initiate the game and not end until user asks to or someone wins.
	The whole game logic is in this function. It will control the flow of the game.

Parameters: none.

Return Value: Returns true if the game ends with someone winning. it returns false if game
	is saved.

Local Variables:
	returnedDice, a pointer. It holds the returned dice one a player makes a move.

Algorithm: 
	1. Print the board.
	2. Ask if user want's to save the game
	3. If no, ask the user if they want hint.
	4. If no, ask the user to make the move.
	5. Change the player and run algorithm for computer.

Assistance Received: none
********************************************************************* */
// this will update if the game is finished or it is just saved.
bool game::startGame() {

	while (!isDone) {

		// Prints the board first.
		boardView.printBoard();

		//char userInputForSaving;
		// Prompt the user if they want to keep playing
		do {
			cout << "Do you want to keep playing or save the game? (S for save/ P for keep playing):: ";
			cin >> userInputForSaving;

			userInputForSaving = tolower(userInputForSaving);
			if (userInputForSaving == 's') {
				return false;
			}
		} while (userInputForSaving != 'p' && userInputForSaving != 's');
		

		if (!isComputersTurn) {
			// Let human play the game.
			Dice * returnedDice = humanP->play(board);

			// Check if human's move eats any of computer's dices.
			if (returnedDice != NULL) {
				// Here, the dice that was lost is returned.
				if (returnedDice->isPlayerKing()) {
					isDone = true;
					computerWin = false;
					cout << "####-----------------####--------------------####" << endl;
					cout << "YOU WON!!!!!!!!!!!!" << endl;
					cout << "Go brag about it! You won the computer!" << endl << endl;
					boardView.printBoard();
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
					boardView.printBoard();
				}
				else {
					returnedDice->setKilled();
				}
			}
		}

		
		// Changes the turn of computer.
		isComputersTurn = !isComputersTurn;

	}


	// Returns true to indicate that the game is complete.
	return true;
}
