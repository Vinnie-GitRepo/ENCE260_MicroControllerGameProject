#include "Tables.h"

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
			break;
		case 'S':
			if(Resv == 'P') { 
				Won = 1;
			}
			break;

		case 'P':
			if(Resv == 'R') { 
					Won = 1;
			}
			break;

	}
	return Won;
}
