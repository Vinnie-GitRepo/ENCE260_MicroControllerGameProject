/*
# File:   Animations.h
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board
*/

#ifndef LETTERPICKER_H
#define LETTERPICKER_H

/** Displays the scores*/
int DisplayScores(char Wins, char Loses);

/** Shows the gold you have */
int DisplayGold(char Gold, char OtherGold);

/** Displays text saying if you won or lost */
int DisplayWinner(char Wins);

/** Displays winners of GTS and the type of victory/loss it was */
int DisplayWinnerGTS(char Wins, char Gold, char OtherGold);

#endif
