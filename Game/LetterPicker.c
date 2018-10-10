/*
# File:   Animations.c
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board

LetterPicker.o: LetterPicker.c LetterPicker.h  ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/navswitch.h ../../../fonts/font5x7_1.h ../../../utils/font.h ../../../utils/pacer.h ../../../utils/tinygl.h 
	$(CC) -c $(CFLAGS) $< -o $@

LetterPicker.o */

#include "LetterPicker.h"
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "Tables.h"
#include "Animations.h"

#define PACER_RATE 1000
#define MESSAGE_RATE 10
int NavSwitch_Val = 0;
char character = 'R';

/* Waits for lock of what letter has been picked */

int WaitForLock(void)
{
	tinygl_init (PACER_RATE);
    	tinygl_font_set (&font5x7_1);
    	tinygl_text_speed_set (MESSAGE_RATE);
	while(1) {
		
		/*Wait times for things to update */
		pacer_wait ();
		tinygl_update ();
		navswitch_update ();
		display_character(character);
		/* setting up to go up characters and down to go down characters */
		if (navswitch_push_event_p (NAVSWITCH_NORTH)) {	
		    NavSwitch_Val = (NavSwitch_Val + 1)%3;
		}
		if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
		    NavSwitch_Val = (NavSwitch_Val - 1)%3;
		}
			
		/* This locsk in the letter picked and clears the board from all presets for the animations */
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			ClearBoard();
			tinygl_clear();
			tinygl_update ();
			break;
		}
		/* gets the character corrsponding to the value */
		character = GetPSR(NavSwitch_Val);
	}
	return 1;
}
