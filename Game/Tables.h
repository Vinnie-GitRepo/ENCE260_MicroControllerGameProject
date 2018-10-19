/***********************************************************************
# File:          Tables.h
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   Module handling the conditionals called in our games
# Last Modified: 17 OCT 2018
***********************************************************************/

#ifndef TABLES_H
#define TABLES_H


/** Get GTS from NavSwitch_Val */
char getGTS(int navswitchVal);

/** Get end of round stats */
int determineRoundOutcome(char character, char receivedChar);

/** Converts the char representing a gold value to an int for calculations*/
int charToInt(char gold);

#endif
