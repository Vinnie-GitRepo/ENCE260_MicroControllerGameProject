/***********************************************************************
# File:          Animations.h
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for LED game animations on the fun kit
# Last Modified: 17 OCT 2018
***********************************************************************/

#ifndef ANIMATIONS_H
#define ANIMATIONS_H


/** Clears the board form PIO inputs */
void clearBoard (void);

/** Fills the board with on LED's */
void fillBoard (void);

/** Fills the board with  LEDS in a nice way */
int RollFill (void);

/** Fills the board with  LEDS in a nice way but fast */
int rollFill(void);

/** Fixes the board with  LEDS in a nice way */
int rollDel(void);

/** Displays character */
void displayCharacter(char character);

#endif
