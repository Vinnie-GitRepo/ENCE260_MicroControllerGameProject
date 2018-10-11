#include "Tables.h"
#include "tinygl.h"

/* Gets the Symbol for paper scisosrs or rock, from an int mod 3 */
void GetMenu(int Thing)
{
	char* Menu = " PAPER SCISSORS ROCK";
	switch(Thing)
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
char GetPSR(int Thing)
{
	char character = 'R';
	switch(Thing)
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

/* Gets who won out of two results then returns 1 for won 0 for not won */
int WhoWon(char character, char Resv)
{
	int Won = 0;
	switch(character)
	{
		case 'R':
			if(Resv == 'S') { 
				Won = 1;
			}
			if(Resv == 'R') {
				Won = 2;
			}
			break;
		case 'S':
			if(Resv == 'P') { 
				Won = 1;
			}
			if(Resv == 'S') {
				Won = 2;
			}
			break;

		case 'P':
			if(Resv == 'R') { 
				Won = 1;
			}
			if(Resv == 'P') {
				Won = 2;
			}
			break;

	}
	return Won;
}
