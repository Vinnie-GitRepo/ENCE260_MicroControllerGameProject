#include "Tables.h"
#include "tinygl.h"

/* Gets the Symbol for paper scisosrs or rock, from an int mod 3 */
void GetMenu(int NavSwitch_Val)
{
	char* Menu = " PAPER SCISSORS ROCK";
	switch(NavSwitch_Val)
		{
			case 0:
				Menu = " PAPER SCISSORS ROCK";
				break;
			case 1:
				Menu = " GOLD THIEF STEAL";
				break;
			case 2:
				Menu = " QUIT";
				break;
		}
	tinygl_text(Menu);
}


/* Gets the Symbol for paper scisosrs or rock, from an int mod 3 */
char GetPSR(int NavSwitch_Val)
{
	char character = 'R';
	switch(NavSwitch_Val)
	{
		case 0:
			character = 'R';
			break;
		case 1:
			character = 'S';
			break;
		case 2:
			character = 'P';
			break;
	}
	return character;
}

/* Get gold steal trap from int */
char GetGTS(int NavSwitch_Val)
{
	char character = 'G';
	switch(NavSwitch_Val)
	{
		case 0:
			character = 'G';
			break;
		case 1:
			character = 'S';
			break;
		case 2:
			character = 'T';
			break;
	}
	return character;
}

int CheapInt(char Gold) {
	int GoldInt = 0;
	switch(Gold)
	{
		case '0':
			GoldInt = 0;
			break;
		case '1':
			GoldInt = 1;
			break;
		case '2':
			GoldInt = 2;
			break;
		case '3':
			GoldInt = 3;
			break;
		case '4':
			GoldInt = 4;
			break;
	}

	return GoldInt;
}

/* claculates the diffrent types of round endings */
int RoundEnd(char character, char Received_Char)
{
	/* Defults to if both players did Gold */
	int Won = 1;
	switch(character)
	{
		/*If you went gold and they stole it */
		case 'G':
			if(Received_Char == 'S') { 
				Won = 0;
			}
			break;

		/*If you went Trap and they went steal, Therefore you just win */
		case 'T':
			if(Received_Char == 'S') { 
				Won = 3;
			}
			break;
		
		/*If you went Steal and they went trap, Therefore you just lose */
		case 'S':
			if(Received_Char == 'T') { 
				Won = -1;
			}
			if(Received_Char == 'S') {
				Won = 2;
			}

	}
	/* Won1 = You did Gold
	Won2 = You stole Gold
	Won3 = You Trapped them
	Won4 = You trapped but got nothing
	Won5 = You Both did Gold
	Won6 = They trapped on got nothing
	Won0 = You're gold got stolen
	Won-1 = You stole and got trapped */
	return Won;
}

/* Gets who won out of two results then returns 1 for won 0 for not won */
int WhoWon(char character, char Received_Char)
{
	int Won = 0;
	switch(character)
	{
		case 'R':
			if(Received_Char == 'S') { 
				Won = 1;
			}
			if(Received_Char == 'R') {
				Won = 2;
			}
			break;
		case 'S':
			if(Received_Char == 'P') { 
				Won = 1;
			}
			if(Received_Char == 'S') {
				Won = 2;
			}
			break;

		case 'P':
			if(Received_Char == 'R') { 
				Won = 1;
			}
			if(Received_Char == 'P') {
				Won = 2;
			}
			break;

	}
	return Won;
}
