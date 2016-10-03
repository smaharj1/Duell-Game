/************************************************************
* Name:  Sujil Maharjan                                    *
* Project : Project 1, Duell game                          *
* Class : Organization of Programming Language(CMPS 366-01)*
* Date : 10-5-2016                                         *
************************************************************/
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
	bool openGame(string filename, Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore);

private :
	ofstream ofile;
	ifstream ifile;
};

