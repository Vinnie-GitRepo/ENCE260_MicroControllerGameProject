#ifndef ANIMATIONS_H
#define ANIMATIONS_H

/** Clears the board form PIO inputs */
void ClearBoard (void);

/** Fills the board with on LED's */
void FillBoard (void);

/** Fills the board with  LEDS in a nice way */
int RollFill (void);

/** Fixes the board with  LEDS in a nice way */
int RollDel (void);

#endif
