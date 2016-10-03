/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "tournament.h"

tournament::tournament()
{
	totalGames = 0;
	humanScore = 0;
	computerScore = 0;

	fileFunction = new FileHandler();
}


tournament::~tournament()
{
}

void tournament::printWelcomeMessage() {
	cout << "Welcome to the wonderful game of Duell" << endl;
	cout << "We are very delighted that you chose to play this game" << endl;
	cout << "---------------------------x---------------------------" << endl;
}

void tournament::startGame() {
	char userInput;
	cout << "Do you want to start a new game (Y/N) or open existing (O)? :: " << endl;
	cin >> userInput;
	game * newGame;

	bool isGameCompleted = true;

	userInput = tolower(userInput);
	while (userInput == 'y' || userInput == 'o') {

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
			} while (!fileFunction->openGame(filename, tempBoard, isComputersTurn, computerScore, humanScore));

			newGame = new game(tempBoard, isComputersTurn);
		}
		isGameCompleted = newGame->startGame();

		if (isGameCompleted) {
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

		cout << "----Do you want to play another game (Y/N)? :: " << endl;
		cin >> userInput;

		userInput = tolower(userInput);
		if (userInput == 'n') {
			printScore();
		}
	}
}

string tournament::inputFile() {
	string fileName;
	cout << "Please enter the name of the file with the extension (.txt file needed):: ";
	cin >> fileName;

	return fileName;
}

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