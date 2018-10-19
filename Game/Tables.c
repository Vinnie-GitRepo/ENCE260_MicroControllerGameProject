/***********************************************************************
# File:          Tables.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module handling the conditionals called in our games
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "Tables.h"
#include "tinygl.h"

#define STOLEN_GOLD 0
#define OPPONENT_TRAPPED 3
#define PLAYER_TRAPPED -1
#define NOTHING_HAPPENED 1



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
    int outCome = NOTHING_HAPPENED;
    switch (character)
    {
        // If you went gold and they steal, you lose the round
        case 'G':
            if (received_char == 'S') {
                outCome = STOLEN_GOLD;
            }
            break;

        // If you went Trap and they went steal, you win immediately
        case 'T':
            if (received_char == 'S') {
                outCome = OPPONENT_TRAPPED;
            }
            break;

        // If you went Steal and they went trap, you lose immediately
        case 'S':
            if (received_char == 'T') {
                outCome = PLAYER_TRAPPED;
            }
            break;
    }

    return outCome;
}



