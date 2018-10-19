/***********************************************************************
# File:          LetterPicker.h
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for our assignment's text processing
# Last Modified: 17 OCT 2018
***********************************************************************/

#ifndef LETTERPICKER_H
#define LETTERPICKER_H



/** Displays how to play the games */
int displayInfo(void);

/** Shows the gold you have */
int displayGold(char playerGold);


/** Displays winners of GTS and the type of victory/loss it was */
int displayWinner(char wins, char playerGold, char opponentGold);

#endif
