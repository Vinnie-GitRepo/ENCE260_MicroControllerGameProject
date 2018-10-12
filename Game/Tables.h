/*
# File:   Tables.h
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Switch cases for the game.
*/

#ifndef TABLES_H
#define TABLES_H

/** GET Menu from NavSwitch_Val  */
void GetMenu(int NavSwitch_Val);

/** Get GTS from NavSwitch_Val */
char GetGTS(int NavSwitch_Val);

/** GET PSR from NavSwitch_Val  */
char GetPSR(int NavSwitch_Val);

/** Get end of round stats */
int RoundEnd(char character, char Received_Char);

/** Get who won */
int WhoWon(char character, char Received_Char);



#endif
