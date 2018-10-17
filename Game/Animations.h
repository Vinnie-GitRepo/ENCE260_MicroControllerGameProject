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
void ClearBoard (void);

/** Fills the board with on LED's */
void FillBoard (void);

/** Fills the board with  LEDS in a nice way */
int RollFill (void);

/** Fills the board with  LEDS in a nice way but fast */
int RollFillGTS(void);

/** Fixes the board with  LEDS in a nice way */
int RollDel (void);

/** Displays character aee */
void display_character (char character);

#endif
