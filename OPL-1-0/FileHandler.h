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

/*
	This class handles opening a new game as well as saving the game in a text file.
*/
class FileHandler
{
public:
	// Default constructor for the class.
	FileHandler();
	~FileHandler();

	// Saves the game into the text file input by the user.
	void saveGame(string filename, Board * board, bool isComputer, int computerScore, int humanScore);

	// opens the game from the text file input form the user.
	bool openGame(string filename, Board * tempBoard, bool &isComputersTurn, int &computerScore, int &humanScore);

private :

	// Input and output streams of the file.
	ofstream ofile;
	ifstream ifile;
};

