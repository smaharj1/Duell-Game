#pragma once

#include<fstream>
#include"Board.h"
#include<string>
#include<iostream>
#include<sstream>
#include<vector>

using namespace std;


class FileHandler
{
public:
	FileHandler(string filename);
	~FileHandler();

	void saveGame(Board * board, bool isComputer, int computerScore, int humanScore);
	void openGame(Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore);

	

private :
	string filename;
	ofstream ofile;
	ifstream ifile;

};

