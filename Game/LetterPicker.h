/*
# File:   Animations.h
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board
*/

#ifndef LETTERPICKER_H
#define LETTERPICKER_H

/** Clears the board form PIO inputs */
int DisplayScores(char Wins, char Loses);

/** Shows the gold you have */
int DisplayGold(char Gold);

/** Clears the board form PIO inputs */
int DisplayWinner(char Wins);

/** Displays winners of GTS */
int DisplayWinnerGTS(char Wins, char Gold, char OtherGold);

#endif
