/***********************************************************************
# File:          Tables.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   Handles the conditionals called throughout our games
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "Tables.h"
#include "tinygl.h"


/*
 * Gets the selection for the main menu, from an int mod 3
 */
void GetMenu(int navswitch_val)
{
    char* menu = " PAPER SCISSORS ROCK";
    switch (navswitch_val)
        {
            case 0:
                menu = " PAPER SCISSORS ROCK";
                break;

            case 1:
                menu = " GOLD TRAP STEAL";
                break;

            case 2:
                menu = " QUIT";
                break;
        }

    tinygl_text(menu);
}



/*
 * Gets the symbol for paper, scissors, or rock, from an int mod 3
 */
char GetPSR(int navswitch_val)
{
    char character = 'R';
    switch (navswitch_val)
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



/*
 * Get gold steal trap from int
 */
char GetGTS(int navswitch_val)
{
    char character = 'G';
    switch (navswitch_val)
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



/*
 * Converts the char representing a gold value to an int for calculations
 */
int CheapInt(char Gold) {
    int gold_int = 0;
    switch (Gold)
    {
        case '0':
            gold_int = 0;
            break;

        case '1':
            gold_int = 1;
            break;

        case '2':
            gold_int = 2;
            break;

        case '3':
            gold_int = 3;
            break;

        case '4':
            gold_int = 4;
            break;
    }

    return gold_int;
}



/*
 * Determines the round ending based on player-choices
 */
int determineRoundOutcome(char character, char received_char)
{
    // Defaults to 1 if both players did gold
    int won = 1;
    switch (character)
    {
        // If you went gold and they steal, you lose the round
        case 'G':
            if (received_char == 'S') {
                won = 0;
            }
            break;

        // If you went Trap and they went steal, you win immediately
        case 'T':
            if (received_char == 'S') {
                won = 3;
            }
            break;

        // If you went Steal and they went trap, you lose immediately
        case 'S':
            if (received_char == 'T') {
                won = -1;
            }
            if (received_char == 'S') {
                won = 2;
            }
            break;
    }

    return won;
}



/*
 * Gets who won out of two results then returns 1 for won 0 for not won
 */
int DetermineWinner(char character, char received_char)
{
    int won = 0;
    switch (character)
    {
        case 'R':
            if (received_char == 'S') {
                won = 1;
            }
            if (received_char == 'R') {
                won = 2;
            }
            break;

        case 'S':
            if (received_char == 'P') {
                won = 1;
            }
            if (received_char == 'S') {
                won = 2;
            }
            break;

        case 'P':
            if (received_char == 'R') {
                won = 1;
            }
            if (received_char == 'P') {
                won = 2;
            }
            break;
    }

    return won;
}
