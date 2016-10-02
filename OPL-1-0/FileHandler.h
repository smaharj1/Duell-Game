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
	FileHandler();
	~FileHandler();

	void saveGame(string filename, Board * board, bool isComputer, int computerScore, int humanScore);
	void openGame(string filename, Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore);

	

private :
	ofstream ofile;
	ifstream ifile;

};

