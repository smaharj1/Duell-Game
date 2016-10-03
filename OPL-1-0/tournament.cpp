/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "tournament.h"

/* *********************************************************************
Function Name: tournament
Purpose: Default constructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
tournament::tournament()
{
	// Initializes all the class variables to 0.
	totalGames = 0;
	humanScore = 0;
	computerScore = 0;

	fileFunction = new FileHandler();
}

/* *********************************************************************
Function Name: tournament
Purpose: Destructor

Parameters:

Return Value:

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
tournament::~tournament()
{
}

/* *********************************************************************
Function Name: printWelcomeMessage
Purpose: To print the welcome message to the player

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void tournament::printWelcomeMessage() {
	cout << "Welcome to the wonderful game of Duell" << endl;
	cout << "We are very delighted that you chose to play this game" << endl;
	cout << "---------------------------x---------------------------" << endl;
}

/* *********************************************************************
Function Name: startGame
Purpose: To start the game based on user's choices i.e. whether to start a new game or load up the game that
	is already saved.

Parameters: none.

Return Value: none.

Local Variables: 
	userInput, a character. It holds the character entered by the user
	newGame, a pointer. It holds the pointer to the game class.
	isGameCompleted, a boolean. It determines if the game has been completed or it was interrupted.
	tempBoard, a pointer. It holds the pointer to the board.
	filename, a string. It holds the name of the file that user wants to save/open.
	isComputersTurn, a boolean. It determines if it is user's or computer's turn.

Algorithm: 
	1. Ask the user if they want to start a new game.
	2. If yes, start a new game. If no, open a game that user prefers to.

Assistance Received: none
********************************************************************* */
void tournament::startGame() {
	// Asks the user if they want to start a new game.
	char userInput;
	cout << "Do you want to start a new game (Y/N) or open existing (O)? :: " << endl;
	cin >> userInput;

	// Declares a pointer that will point to a new game.
	game * newGame;

	bool isGameCompleted = true;

	userInput = tolower(userInput);

	// Goes through the process of starting a new game or loading the game until user wants.
	while (userInput == 'y' || userInput == 'o') {
		// If user says 'y', then it starts a new game. Else, it prompts the user to give
		// the filename of the file they want to open.
		if (userInput == 'y') {
			totalGames++;
			newGame = new game();
		}
		else {
			Board * tempBoard = new Board();
			bool isComputersTurn;
			string filename;
			do {
				filename = inputFile();
				// Inputs the filename and tries to open the file.
				// This modifies all the tempBoard and the tournament variables that holds the status of the game.
			} while (!fileFunction->openGame(filename, tempBoard, isComputersTurn, computerScore, humanScore));

			newGame = new game(tempBoard, isComputersTurn);
		}

		// Starts the new game.
		isGameCompleted = newGame->startGame();

		// Once the game is returned, it checks if the game was ended or interrupted. 
		// Displays the messages according to the status.
		if (isGameCompleted) {
			// Checks who is the winner of the round and adds the score accordingly.
			if (newGame->isComputerWinner()) {
				computerScore++;
			}
			else humanScore++;
		}
		else {
			// Game needs to be saved.
			string filename = inputFile();
			fileFunction->saveGame(filename, newGame->getBoard(), newGame->getIfComputerTurn(), computerScore, humanScore);
		}

		// Prompts the user if they want to start a new game.
		cout << "----Do you want to play another game (Y/N)? :: " << endl;
		cin >> userInput;

		userInput = tolower(userInput);
		if (userInput == 'n') {
			printScore();
		}
	}
}

/* *********************************************************************
Function Name: inputFile
Purpose: To ask user for the name of the file.

Parameters: none.

Return Value: Returns the name of the file entered by the user

Local Variables: 
	filename, a string. It holds the name of the file.

Algorithm: none.

Assistance Received: none
********************************************************************* */
string tournament::inputFile() {
	string fileName;
	cout << "Please enter the name of the file with the extension (.txt file needed):: ";
	cin >> fileName;

	return fileName;
}

/* *********************************************************************
Function Name: printScore
Purpose: To print the score 

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
void tournament::printScore() {
	cout << "-------------Score board---------------" << endl;
	cout << "Computer won: " << computerScore << endl;
	cout << "Human won: " << humanScore << endl;
	if (computerScore > humanScore) {
		cout << "The winner is Computer!" << endl;
	}
	else if (computerScore < humanScore) {
		cout << "You are the winner!" << endl;
	}
	else {
		cout << "The game is a draw!" << endl;
	}
	cout << "---------------------------------------" << endl;
}