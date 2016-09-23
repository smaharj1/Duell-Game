#include "FileHandler.h"



FileHandler::FileHandler(string filename)
{
	this->filename = filename;
}


FileHandler::~FileHandler()
{
}

void FileHandler::saveGame(Board * board, bool isComputer, int computerScore, int humanScore) {
	ofile.open(filename);

	if (!ofile) {
		cout << "Could not save the file due to exceptions" << endl;
		return;
	}

	ofile << "board:" << endl;
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
	if (isComputer) {
		ofile << "Turn: " << "computer";
	}
	else {
		ofile << "Turn: " << "human";
	}
	ofile << endl << endl;

	ofile << "HumanScore: " << humanScore << endl;
	ofile << "ComputerScore: " << computerScore << endl;

	ofile.close();

}

void FileHandler::openGame(Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore) {
	ifile.open(filename);
	string line;
	int lineIndex = 0;
	string board[8][9];
	vector<string> tmp;
	
	while (getline(ifile, line)) {
		if (lineIndex == 0) {
			lineIndex++;
			continue;
		}
		if (lineIndex <= 8 && lineIndex >0) {
			stringstream sss(line);
			string str;
			int j = 0;
			while (sss >> str) {
				board[lineIndex - 1][j] = str;
				j++;
			}
			
		}
		else {
			if (line.empty()) continue;

			stringstream ss(line);
			string str;
			tmp.clear();
			while (ss >> str) {
				tmp.push_back(str);
			}
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


	tempBoard->setBoard(board);
}