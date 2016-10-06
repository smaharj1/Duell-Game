#Duell
*CHILD OF CHESS*
Sujil Maharjan | Organization of Programming language | 10/4/2016 

##Class Descriptions
1.	Dice: 
This class holds all the information needed for a dice and it consists of all the functionalities that a die can perform. The primary functionalities include rolling of the dices.
2.	Board:
This is the model class of the board of the game. It handles all the functionalities performed on the board. The primary functionalities include handling movement of a die and performing various verifications of the movement.
3.	Algorithm:
This class holds the logic of the game. This is an automation provided for the computer player. However, it can also be used for human. The algorithm plays offense and tries to win the game.
4.	BoardView:
It holds the view of the board and helps output the modifications of the board. 
5.	Cell:
It holds the value of one square of the board. Each box of the board is represented as a square. So, the cell will consist of a die of the board. 
6.	Computer:
This class holds the functionalities for a computer player. It is inherited from Player class. So, the functionalities are customized such that the computer will play the game using the offensive algorithm against the opponent. 
7.	Human:
This class holds the functionalities for a human player. It is inherited from Player class. So, the functionalities are customized such that user can make moves or choose from many different options.
8.	Player:
This is a base class for all the players. This class cannot have an instance by itself. It will function as a base class to as many players as the user needs.
9.	FileHandler:
This class handles the actions for the files. It assists in saving and opening the game such that it assists other classes by rendering files to save or load a game.
10.	Game:
This class handles a single round of the tournament. Once the tournament starts, this class will start the game and acts as the controller for human, board and model. 
11.	Location:
This class holds the location of the board. This class is not human friendly. So, indexes start from 0.
12.	Tournament:
This class start the tournament of Duell. It prompts the user if they want to start a new tournament or start from the point they left the game. 
13.	TreeNode:
This class holds the information of a die and its current location. This provides as a node if algorithm goes many steps further and wants to go through various depth.

#Algorithm of automated game:
Following algorithm is used to make a move:
1.	Check if the player can win the game by looping through each and every dice of the player and confirming if the movement is possible for the given location.
2.	Check if the king is in threat by opponent.
a.	If yes, then check if the threat can be minimized by eating the opponent. If it can be eaten, then eat the opponent.
b.	If no, then move the king to either direction that is a safe play. This will make the opponent to strategize again to get the king.
3.	Check if opponent’s players can be eaten. Loop through each and every dices and check if you can eat any opponents.
4.	Make a safe and offensive move. This will move the player to the closest square to the opponent where the die is safe. After the movement, it is sure that opponent will not be able to eat the recently moved die.

#How to run
To run the program, you need to run the source.cpp file.

#Bug Report
1.	The understanding of the question was a bit different. The bug currently is that if any dice of a player moves to the opponent’s key square, the game ends. 
Feature report:
1.	The program explains why the move was made. It does not simply give the move that was made. It tries to explain why it is a better move. 
2.	The user has the choice to name the file while saving it.

#Missing features:
1.	There is no block functionality for the threat to the key die. Instead, the key die is moved since it is a simple and elegant solution. It helps as it makes the opponent move more dices to strategize to try to eat the king again.
Screenshots
