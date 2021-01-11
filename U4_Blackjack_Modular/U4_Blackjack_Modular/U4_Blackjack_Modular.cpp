// U4_Blackjack_Modular.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Hampton U4 Blackjack Modular

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <string>

using namespace std;

//Declare constant values for all literal values except zero and one
const int ACE = 11;
const int TWO = 2;
const int THREE = 3;
const int FOUR = 4;
const int FIVE = 5;
const int SIX = 6;
const int SEVEN = 7;
const int EIGHT = 8;
const int NINE = 9;
const int TEN = 10;
const int JACK = 10;
const int QUEEN = 10;
const int KING = 10;

/* Create the getCard() function used to create a random number and then assign 
that number to a string value. */
string getCard() {

	//Generate a random number from 1-13 and assign that value to card_num.
	int card_num = rand() % 13 + 1;

	//Convert card_num to an int value and assign it to playing_card.
	string playing_card = to_string(card_num);

	/* If the value assigned to playing_card is 1, 11, 12, or 13 and if
	else if statement will change the value to the appropriate string value. */
	if (playing_card == "1") {
		playing_card = "A";
	}
	else if (playing_card == "11") {
		playing_card = "J";
	} 
	else if (playing_card == "12") {
		playing_card = "Q";
	}
	else if (playing_card == "13") {
		playing_card = "K";
	}

	//Return the string variable playing_card;
	return playing_card;
}

/* Create the getCardValue function which will take a string paramiter and
convert it to an int value. */
int getCardValue(string playing_card) {
	
	//Initialize card_value to zero.
	int card_value = 0;

	/* Taking the value from playing_card and if else if statement will
	set the appropriate constant value to the card_value variable */
	if (playing_card == "A") {
		card_value = ACE;
	}
	else if (playing_card == "2") {
		card_value = TWO;
	}
	else if (playing_card == "3") {
		card_value = THREE;
	}
	else if (playing_card == "4") {
		card_value = FOUR;
	}
	else if (playing_card == "5") {
		card_value = FIVE;
	}
	else if (playing_card == "6") {
		card_value = SIX;
	}
	else if (playing_card == "7") {
		card_value = SEVEN;
	}
	else if (playing_card == "8") {
		card_value = EIGHT;
	}
	else if (playing_card == "9") {
		card_value = NINE;
	}
	else if (playing_card == "10") {
		card_value = TEN;
	}
	else if (playing_card == "J") {
		card_value = JACK;
	}
	else if (playing_card == "Q") {
		card_value = QUEEN;
	}
	else if (playing_card == "K") {
		card_value = KING;
	}

	//Return card_value.
	return card_value;
}

int main() {


	//Declare the seed variable unsigned so only possitive integers may be used.
	unsigned seed;

	//Use the time function to get a seed value for srand() function
	seed = time(0);
	srand(seed);

	//Declare the userName variable
	string userName;

	//Declare the magicKey char variable.
	char magicKey;


	//Declare the playerTotalScore and dealerTotalScore variables.
	int playerTotalScore = 0;
	int dealerTotalScore = 0;

	//Print out the opening line of the program
	cout << "Welcome to Black-Jack\n" << endl;

	//Prompt the user to enter a name to add string data to the userName variable
	cout << "Please enter your name: ";
	//userName is populated with a user input
	cin >> userName;

	//Prompt the user to press a key to to begin the game.
	cout << "\nHello " << userName
		<< ", press any key to begin the game.";

	//Populate the magicKey variable with the getch() function.  
	//Until a key is pressed the program will be paused.
	magicKey = _getch();
	cout << "  " << endl;
	cout << "  " << endl;


	//Declare the playerFirstCard variable by calling the getCard() function.
	string playerFirstCard = getCard();
	cout << "\n" << userName << ", your first card is " << playerFirstCard << "\n" << endl;

	//Call the getCardValue function using playerFirstCard to add the returned 
	//	value to playerTotalScore.
	playerTotalScore += getCardValue(playerFirstCard);





	//Declare the dealerFirstCard variable by calling the getCard() function.
	string dealerFirstCard = getCard();
	cout << "The dealer's first card is " << dealerFirstCard << "\n" << endl;

	//Call the getGetCard function using dealerFirstCard to add the returned 
	//	value to dealerTotalScore
	dealerTotalScore += getCardValue(dealerFirstCard);





	//Declare the playerSecondCard variable by calling the getCard() function.
	string playerSecondCard = getCard();
	cout << userName << ", your second card is " << playerSecondCard << "\n" << endl;

	//Call the getCardValue function using playerSecondCard to add the returned 
	//	value to playerTotalScore.
	playerTotalScore += getCardValue(playerSecondCard);




	//Display the userName and what the playerTotalScore value is.
	cout << userName << ", your score for this hand is " << playerTotalScore << endl;
	


	//Declare the dealerSecondCard variable by calling the getCard() function.
	string dealerSecondCard = getCard();


	//Prompt the user to enter any key to continue the program.
	cout << "\nThe dealer's second card is face-down. Press any key to turn the dealer's card over.";
	
	
	//Populate the magicKey variable with the getch() function.  
	//Until a key is pressed the program will be paused.
	magicKey = _getch();
	cout << "  " << endl;
	cout << "  " << endl;
	cout << "  " << endl;


	//Call the getCardValue function using dealerSecondCard to add the returned 
	//	value to dealerTotalScore.
	cout << "The dealer's second card is " << dealerSecondCard << "\n" << endl;
	dealerTotalScore += getCardValue(dealerSecondCard);
	cout << "The dealer's score for this hand is " << dealerTotalScore << endl;


	//If the dealerTotalScore is greater than the playerTotalScore inform
	// the user dealerTotalScore was greater and the dealer has won, unless the 
	//  dealerTotalScore is greater than 21, then inform user they have won.
	if (dealerTotalScore > playerTotalScore) {
		if (dealerTotalScore > 21) {
			cout << "\nYou have won this hand!" << endl;
		}
		else {
			cout << "\nThe dealer has won this hand." << endl;
		}
	}


	//If the playerTotalScore is greater than the dealerTotalScore inform
	// the user playerTotalScore was greater and they have won, unless the 
	//  playerTotalScore is greater than 21, then inform user the dealer has won.
	else if (playerTotalScore > dealerTotalScore) {
		if (playerTotalScore > 21) {
			cout << "\nThe dealer has won this hand." << endl;
		}
		else {
			cout << "\nYou have won this hand!" << endl;
		}
	}

	//If both the playerTotalScore and dealerTotalScore are over 21
	else if (playerTotalScore > 21 && dealerTotalScore > 21) {
		cout << "\nBoth the player and the dealer went bust." << endl;
	}

	//If playerTotalScore equals dealerTotalScore than inform the user of a tie.
	else {
		cout << "\nYou have tied the dealer." << endl;
	}

	//Print final continuation line.
	cout << "\nPress any key to continue." << endl;

	//Populate the magicKey variable with the getch() function.  
	//Until a key is pressed the program will be paused.
	magicKey = _getch();
	cout << "  " << endl;
	cout << "  " << endl;

	//Print the final farewell statement before ending program.
	cout << "\nThank you for playing!" << endl;

}


