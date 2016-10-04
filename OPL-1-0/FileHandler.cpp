/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
#include "FileHandler.h"

/* *********************************************************************
Function Name: FileHandler
Purpose: Default Constructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
FileHandler::FileHandler()
{
	// no need of initializations.
}

/* *********************************************************************
Function Name: ~FileHandler
Purpose: Destructor

Parameters: none.

Return Value: none.

Local Variables: none.

Algorithm: none.

Assistance Received: none
********************************************************************* */
FileHandler::~FileHandler()
{
}

/* *********************************************************************
Function Name: saveGame
Purpose: To save the current game according to the serialization formate provided.

Parameters:
	filename, a string. It holds the name of the file.
	board, a pointer. It holds the pointer to the original board.
	isComputer, a boolean. It holds if the player is computer or not.
	computerScore, an integer. It holds the total computer score.
	humanScore, an integer. It holds the total human score.

Return Value: none.

Local Variables: none.

Algorithm: 
	1. Make the file.
	2. Print the Board.
	3. Print the computer score.
	4. Print the human score.
	5. Print next player's turn.

Assistance Received: none
********************************************************************* */
void FileHandler::saveGame(string filename, Board * board, bool isComputer, int computerScore, int humanScore) {
	ofile.open(filename);

	// Check if the file can be opened or not.
	if (!ofile) {
		cout << "Could not save the file due to exceptions" << endl;
		return;
	}

	// Loop through each row and column of the board and print it in the file accordingly.
	ofile << "Board:" << endl;
	for (int index = 0; index < board->getTotalRows(); index++) {
		for (int j = 0; j < board->getTotalColumns(); j++) {
			if (board->getCell(index, j)->isEmpty()) {
				ofile << "  0  ";
			}
			else {
				ofile << "  " << board->getCell(index, j)->getDice()->getValue() << "  ";
			}
		}
		ofile << endl;
	}
	ofile << endl;
	
	// Prints the computer and human scores.
	ofile << "Computer Wins: " << computerScore << endl << endl;
	ofile << "Human Wins: " << humanScore << endl << endl;
	if (isComputer) {
		ofile << "Next Player: " << "computer";
	}
	else {
		ofile << "Next Player: " << "human";
	}
	ofile << endl << endl;

	// Closes the file.
	ofile.close();
}

/* *********************************************************************
Function Name: openGame
Purpose: To open the game provided the file name 

Parameters:
	filename, a string. It holds the name of the file.
	tempBoard, a pointer. It holds the pointer to the original board.
	isComputersTurn, a boolean passed by reference. It holds if the player is computer or not.
	computerScore, an integer passed by reference. It holds the total computer score.
	humanScore, an integer passed by reference. It holds the total human score.

Return Value: Returns true if file is successfully loaded.

Local Variables:
	line, a string. It holds the string of a line.
	lineIndex, an integer. It holds the index of the line. It is helpful for finding out the board's info.
	board[][], a 2d string array. It holds the board info in string format.
	tmp, vector of string. It holds each words separated by spaces for scores and player turns.
	ss, a string stream. It holds the string stream.

Algorithm:
	1. Check for "Board" text.
	2. If found, fill up board string array for next 8 lines.
	3. Store the computer score.
	4. Store the human score.
	5. Store the players turn.

Assistance Received: none
********************************************************************* */
bool FileHandler::openGame(string filename, Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore) {
	ifile.open(filename);

	// Check if the file exists to open.
	if (!ifile) {
		cout << "File not found" << endl;
		return false;
	}

	// Temporary variables initialization and declarations.
	string line;
	int lineIndex = 0;
	string board[8][9];
	vector<string> tmp;
	
	// Go through each lines and store the values accordingly.
	while (getline(ifile, line)) {
		// First line is "board" word. So, skip that.
		if (lineIndex == 0) {
			lineIndex++;
			continue;
		}

		// Go to next 8 lines and store all the values as board info.
		if (lineIndex <= 8 && lineIndex >0) {
			stringstream boardStream(line);
			string str;
			int j = 0;

			// Separate the line by spaces and store each cell info.
			while (boardStream >> str) {
				board[lineIndex - 1][j] = str;
				j++;
			}
		}
		else {
			if (line.empty()) continue;

			stringstream ss(line);
			string str;
			tmp.clear();

			// Go through each words separated by space and then push it in tmp vector.
			while (ss >> str) {
				tmp.push_back(str);
			}

			// If the vector is empty, it means the line only has spaces. So, continue.
			if (tmp.empty()) continue;

			switch(lineIndex) {
			case 11: // This determines the turn of player.
				isComputersTurn = tmp.at(tmp.size() - 1) == "Human" ? false : true;
				break;
			case 9: // This determines total games won by computer
				computerScore = stoi(tmp.at(tmp.size() - 1));
				break;
			case 10: // This determines total games won by human
				humanScore = stoi(tmp.at(tmp.size() - 1));
				break;
			}
		}
		lineIndex++;
	}
	
	// Sets the board.
	tempBoard->setBoard(board);

	return true;
}