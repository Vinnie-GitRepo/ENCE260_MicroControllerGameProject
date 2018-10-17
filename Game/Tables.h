/***********************************************************************
# File:          Tables.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   Handles the conditionals called throughout our games
# Last Modified: 17 OCT 2018
***********************************************************************/

#ifndef TABLES_H
#define TABLES_H

/** GET Menu from NavSwitch_Val  */
void GetMenu(int NavSwitch_Val);

/** Get GTS from NavSwitch_Val */
char GetGTS(int NavSwitch_Val);

/** GET PSR from NavSwitch_Val  */
char GetPSR(int NavSwitch_Val);

/** Get end of round stats */
int determineRoundOutcome(char character, char Received_Char);

/** Get who won */
int determineWinner(char character, char Received_Char);

int CheapInt(char Gold);

#endif
