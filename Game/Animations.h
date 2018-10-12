/*
# File:   Animations.h
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board
*/

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

#endif
