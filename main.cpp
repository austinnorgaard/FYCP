//***************************************************************************
// File Name:     main.cpp
// Author:        Austin Norgaard
// Date:          11/01/19
// Class Name:    CS150-01
// Assignment:    Craps! - Assignment 5
// Purpose:       A game of craps involving a bank, chips, dice with ASCII
//							  graphics, and random number generators.
// Hours Worked:  10
//***************************************************************************

#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

int startingHouseBank = 10200,
		houseBank = startingHouseBank,
		tenSucks1 = 0,
		tenSucks2 = -1,
		dieTotal;

char userChoice = 'o',
		 moreChips,
		 diceTotal = '0';

void drawHeading (string title, char borderChar, int padding);
void getPlayerBuyin (string prompt, int& playerChips);
void drawDieFace (int face);
void drawDiceFace (int face1, int face2);
int rollDie ();
int rollDice (int& dieOne, int& dieTwo);

int main ()
{
	srand (static_cast<unsigned> (time (static_cast<time_t*>(NULL))));

	const string TITLE_STRING = "Craps";

	int random = rand () % 6 + 1,
		  dieFace1Num,
		  dieFace2Num,
		  playerChips = 0,
		  playerCash,
		  playerBet,
		  gameCounter = 1;

	char lastRoll;

	bool bIsWinner,
		   bIsLoser;

	do
	{
		drawHeading (TITLE_STRING, '*', 8);

		getPlayerBuyin ("Enter Player Buy-in: $", playerChips);

		system ("cls");

		do
		{
			if (houseBank == 0)
			{
				drawHeading (TITLE_STRING, '*', 8);
				cout << endl << "We're out of cash. Game Over!" << endl << endl;
				return EXIT_FAILURE;
			}

			system ("cls");

			drawHeading (TITLE_STRING, '*', 8);
			lastRoll = '0';
			bIsLoser = false;
			bIsWinner = false;

			if (playerChips == 0)
			{
				system ("cls");
				drawHeading (TITLE_STRING, '*', 8);
				cout << "Game Over! Out of Chips!" << endl << endl; 
				return EXIT_FAILURE;
			}

			cout << "House Bank: $" << houseBank << endl << "Player Chips: "
				   << playerChips << endl << endl;

			do
			{
				cout << "Enter player bet: ";
				cin >> playerBet;
			} while (playerBet > playerChips);
			
			userChoice = 'o';

			playerChips -= playerBet;

			system ("cls");

			dieFace1Num = rollDie ();
			dieFace2Num = rollDie ();

			drawHeading (TITLE_STRING, '*', 8);

			cout << "Dice Pair (" << dieFace1Num << ", " << dieFace2Num << ")"
				   << endl;

			drawDiceFace (dieFace1Num, dieFace2Num);

			cout << endl;

			rollDice (dieFace1Num, dieFace2Num);
			gameCounter++;
			switch (diceTotal)
			{
				case '7':  cout << "Congratulations! You rolled a 7. You win!"
					              << endl << endl << "Play Again (Y / N): ";
					         cin >> userChoice;
									 while (userChoice != 'y' && userChoice != 'Y' &&
												  userChoice != 'n' && userChoice != 'N')
									 {
											cout << "Invalid Choice! Select Yes or No";
											cin >> userChoice;
								   }
									 bIsWinner = true;
									 break;
				case '0' + 11: cout << "Congratulations! You rolled an 11. You win!"
														<< endl << endl << "Play Again (Y / N): ";
											 cin >> userChoice;
											 while (userChoice != 'y' && userChoice != 'Y' &&
														  userChoice != 'n' && userChoice != 'N')
											 {
													cout << "Invalid Choice! Select Yes or No";
													cin >> userChoice;
											 }
											 bIsWinner = true;
											 break;
				case '2':  cout << "Sorry you rolled a 2. You crapped out!" << endl
												<< endl << "Play Again (Y / N): ";
									 cin >> userChoice;
									 while (userChoice != 'y' && userChoice != 'Y' &&
													userChoice != 'n' && userChoice != 'N')
									 {
											cout << "Invalid Choice! Select Yes or No";
											cin >> userChoice;
									 }
									 bIsLoser = true;
									 break;
				case '3':  cout << "Sorry you rolled a 3. You crapped out!" << endl
												<< endl << "Play Again (Y / N): ";
									 cin >> userChoice;
									 while (userChoice != 'y' && userChoice != 'Y' &&
													userChoice != 'n' && userChoice != 'N')
									 {
											cout << "Invalid Choice! Select Yes or No";
											cin >> userChoice;
									 }
									 bIsLoser = true;
									 break;
				case '0' + 12: cout << "Sorry you rolled a 12. You crapped out!" 
													  << endl << endl << "Play Again (Y / N): ";
											 cin >> userChoice;
											 while (userChoice != 'y' && userChoice != 'Y' &&
															userChoice != 'n' && userChoice != 'N')
											 {
													cout << "Invalid Choice! Select Yes or No";
													cin >> userChoice;
											 }
											 bIsLoser = true;
											 break;
				case '4':  cout << "You must roll a 4 to win. If you roll a 7, "
													 "you lose." << endl;
									 break;
				case '5':	 cout << "You must roll a 5 to win. If you roll a 7, "
													 "you lose." << endl;
									 break;
				case '6':	 cout << "You must roll a 6 to win. If you roll a 7, "
													 "you lose." << endl;
									 break;
				case '8':	 cout << "You must roll an 8 to win. If you roll a 7, "
													 "you lose." << endl;
									 break;
				case '9':	 cout << "You must roll a 9 to win. If you roll a 7, "
													 "you lose." << endl;
									 break;
				case '0' + 10: cout << "You must roll a 10 to win. If you roll a 7, "
															 "you lose." << endl;
											 break;
			}
			lastRoll = diceTotal;

			tenSucks1 = 0;
			tenSucks2 = -1;

			if (dieTotal == 10)
			{
				tenSucks1 = 10;
			}
			system ("pause");
			system ("cls");
			if (userChoice == 'o')
			{
				do
				{


					dieFace1Num = rollDie ();
					dieFace2Num = rollDie ();

					drawHeading (TITLE_STRING, '*', 8);

					cout << "Dice Pair (" << dieFace1Num << ", " << dieFace2Num << ")"
							 << endl;

					drawDiceFace (dieFace1Num, dieFace2Num);

					cout << endl;

					rollDice (dieFace1Num, dieFace2Num);
					if (dieTotal == 10)
					{
						tenSucks2 = 10;
					}
					if (tenSucks1 == tenSucks2)
					{
						cout << "Congratualtions you rolled a " << tenSucks1 <<
										". You win!" << endl << endl << "Play Again"
								 << " (Y / N): ";
						cin >> userChoice;
						while (userChoice != 'y' && userChoice != 'Y' &&
									 userChoice != 'n' && userChoice != 'N')
						{
							cout << "Invalid Choice! Select Yes or No: ";
							cin >> userChoice;
						}
						bIsWinner = true;
					}
					else if (lastRoll == diceTotal)
					{
						cout << "Congratualtions you rolled a " << lastRoll << 
										". You win!" << endl << endl << "Play Again" 
								 << " (Y / N): ";
						cin >> userChoice;
						while (userChoice != 'y' && userChoice != 'Y' &&
									 userChoice != 'n' && userChoice != 'N')
						{
							cout << "Invalid Choice! Select Yes or No: ";
							cin >> userChoice;
						}
						bIsWinner = true;
					}
					else
					{
						gameCounter++;
						if (diceTotal != '7')
						{
							if (tenSucks1 == 10)
							{
								cout << "You must roll a(n) " << tenSucks1
									<< " to win. If you roll a 7, you lose."
									<< endl;
							}
							else
							{
								cout << "You must roll a(n) " << lastRoll
									<< " to win. If you roll a 7, you lose."
									<< endl;
							}
						}
						else if (diceTotal == '7')
						{
							cout << "Sorry, you rolled a 7. You crapped out!"
														 << endl << endl << "Play Again (Y / N): ";
								cin >> userChoice;
								while (userChoice != 'y' && userChoice != 'Y' &&
											 userChoice != 'n' && userChoice != 'N')
								{
									cout << "Invalid Choice! Select Yes or No";
									cin >> userChoice;
								}
								bIsLoser = true;
								break;
						}
					}
					system ("cls");

				} while (gameCounter >= 2 && bIsLoser == false && 
								 lastRoll != diceTotal && bIsWinner == false);
			}
			if (bIsWinner == true)
			{
				playerChips += playerBet * 2;
			}
			if (bIsLoser == true)
			{
				houseBank += playerBet;
			}
		} while (userChoice == 'Y' || userChoice == 'y');

		houseBank = startingHouseBank - playerChips;

		if (playerChips == 0)
		{
			drawHeading (TITLE_STRING, '*', 8);
			do
			{
				cout << "Buy more chips?: ";
				cin >> moreChips;
				system ("cls");
			} while (moreChips != 'y' && moreChips != 'Y' && moreChips != 'n' &&
							 moreChips != 'N');
		}

		playerCash = playerChips;

		playerChips = 0;

		system ("cls");

		drawHeading (TITLE_STRING, '*', 8);

		cout << "Player Cashed Out: $" << playerCash << endl << "House Bank: $"
				 << houseBank << endl;
		do
		{
			cout << endl << "Play Again?: ";
			cin >> moreChips;
		} while (moreChips != 'y' && moreChips != 'Y' && moreChips != 'n' &&
						 moreChips != 'N');

		system ("cls");
	} while (moreChips != 'n' && moreChips != 'N');
	return EXIT_SUCCESS;
}

/****************************************************************************
Function:		 drawHeading

Description: Displays the program title

Parameters:	 title - The title being displayed
						 borderChar - The character bordering the title
						 padding - The amount of space between the character and title

Returned:		 The title of the Assignment
****************************************************************************/
void drawHeading (string title, char borderChar, int padding)
{
	int lineCount = 1,
			totalPadding;

	totalPadding = title.size () + padding * 2;

	do 
	{
		for (int i = 1; i <= totalPadding; i++)
		{
			cout << borderChar;
		}
		lineCount++;
		if (lineCount == 2)
		{
			cout << endl << left << setw (padding) << borderChar << title
					 << right << setw (padding) << borderChar << endl;
		}
		lineCount++;
	} while (lineCount == 1 || lineCount == 3);
	cout << endl << endl;
} 

/****************************************************************************
Function:		 getPlayerBuyin

Description: Outputs a game prompt for the player’s buyin and then inputs
						 the number of chips the player wants to buy. Validate the data
						 such that the player can’t buy more chips than the house has
						 money and the player must buy at least 1 chip. 

Parameters:	 prompt -	A prompt for the user to enter chips
						 playerChips - The value in which the user's buyin chips are
													 stored

Returned:		 The prompt
****************************************************************************/
void getPlayerBuyin (string prompt, int& playerChips)
{
	cout << prompt;
	cin >> playerChips;

	while (playerChips < 1 || playerChips > houseBank)
	{
		cout << prompt;
		cin >> playerChips;
	}
	
	houseBank -= playerChips;
}

/****************************************************************************
Function:		 drawDieFace

Description: Draws the die face that is passed into the parameter.

Parameters:	 face - The number of the face on the die being displayed

Returned:		 The face of the die
****************************************************************************/
void drawDieFace (int face)
{
	ifstream inputFile;
	string dieFace;
	char numFace = '0' + face;
	switch (numFace)
	{
		case '1': inputFile.open ("dice1.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
		case '2': inputFile.open ("dice2.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
		case '3': inputFile.open ("dice3.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
		case '4': inputFile.open ("dice4.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
		case '5': inputFile.open ("dice5.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
		case '6': inputFile.open ("dice6.txt");
							if (inputFile.is_open ())
							{
								while (getline (inputFile, dieFace))
								{
									cout << dieFace << endl;
								}
								inputFile.close ();
							}
							break;
	}
}

/****************************************************************************
Function:		 drawDiceFace

Description: Calls drawDieFace twice showing a special output.

Parameters:	 face1 - The face of dice 1
						 face2 - The face of dice 2

Returned:		 The face of the die
****************************************************************************/
void drawDiceFace (int face1, int face2)
{
	drawDieFace (face1);

	drawDieFace (face2);
}

/****************************************************************************
Function:		 rollDie

Description: Rolls one random die and returns the roll value. Returns an
						 integer between 1 and 6.

Parameters:	 None

Returned:		 A random integer 1-6
****************************************************************************/
int rollDie ()
{
	int random = rand () % 6 + 1;
	return random;
}

/****************************************************************************
Function:		 rollDice

Description: Rolls two random die and returns the roll value. Returns an
						 integer between 2 and 12.

Parameters:	 dieOne - A shared value for die one
						 dieTwo - A shared value for die two

Returned:		 The total die value of die one and two
****************************************************************************/
int rollDice (int& dieOne, int& dieTwo)
{
	dieTotal = dieOne + dieTwo;
	diceTotal = '0' + dieTotal;
	return diceTotal;
}