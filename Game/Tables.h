/*
# File:   Tables.h
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Switch cases for the game.
*/

#ifndef TABLES_H
#define TABLES_H

/** GET Menu from thing  */
void GetMenu(int Thing);

/** Get GTS from thing */
char GetGTS(int Thing);

/** GET PSR from thing  */
char GetPSR(int Thing);

/** Get end of round stats */
int RoundEnd(char character, char Resv);

/** Get who won */
int WhoWon(char character, char Resv);



#endif
