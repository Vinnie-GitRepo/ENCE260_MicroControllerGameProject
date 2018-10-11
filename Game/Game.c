#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_2.h"
#include "pio.h"
#include "Tables.h"
#include "Animations.h"
#include "LetterPicker.h"
#include "Starter.h"
#include "PSR.h"

/* What runs the game */
int main (void)
{
	system_init();
	MenuText_init();
	navswitch_init ();
    int NavSwitch_Val = 0;
	tinygl_text(" PAPER SCISSORS ROCK");
	NavSwitch_Val = 0;

	while (1)
	{
		tinygl_update ();
		navswitch_update ();

		/* setting up to go up characters and down to go down characters */
		if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
			tinygl_clear();
		    NavSwitch_Val = (NavSwitch_Val + 1)%3;
			GetMenu(NavSwitch_Val);

		}
		if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
			tinygl_clear();
		    NavSwitch_Val = (NavSwitch_Val - 1)%3;
		    if(NavSwitch_Val == 0) {
		        NavSwitch_Val = 3;
		    }
			GetMenu(NavSwitch_Val);
		}

		/* This locsk in the letter picked and clears the board from all presets for the isAnimatings */
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			tinygl_clear();
			break;
		}
	}

   while(NavSwitch_Val == 0) {
		PSR_Game();
	}

	tinygl_text(" WORK IN PROGRESS");
	while(1) {
		navswitch_update ();
		tinygl_update ();
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			tinygl_clear();
			break;
		}
	}

	
	
	
}
