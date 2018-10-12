/*
# File:   Animations.c
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board

LetterPicker.o */

#include "LetterPicker.h"
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pio.h"
#include "../fonts/font3x5_1.h"
#include "Tables.h"
#include "Animations.h"
#include "Starter.h"


/* Waits for lock of what letter has been picked */

int DisplayScores(char Wins, char Loses)
{

	system_init();


	ScrollText_init();
	char s[] = { ' ','W', Wins,' ','L', Loses};

	tinygl_text(s);
	TCNT1 = 0;
	while(1) {
		
		tinygl_update();
		navswitch_update ();
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		    break;
		}
	}
	return 1;
}

int DisplayGold(char Gold)
{

	system_init();


	ScrollText_init();
	char s[] = { ' ','G', 'O', 'L', 'D', ' ', Gold};

	tinygl_text(s);
	TCNT1 = 0;
	while(1) {
		
		tinygl_update();
		navswitch_update ();
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		    break;
		}
	}
	return 1;
}

int DisplayWinner(char Wins)
{

	system_init();

	char* s;
	ScrollText_init();
	if(Wins == '5') {
		s = "YOU WON!";
	} else {
		s = "YOU LOST </3";
	}

	tinygl_text(s);
	TCNT1 = 0;
	while(1) {
		
		tinygl_update();
		navswitch_update ();
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		    break;
		}
	}
	return 1;
}

int DisplayWinnerGTS(char Wins, char Gold, char OtherGold)
{

	system_init();

	char* s;
	ScrollText_init();
	if(Wins == 3) {
		s = "YOU TRAPPED THEM YOU WIN";
	} else if(Wins == -1){
		s = "YOU GOT TRAPPED YOU LOSE";
	} else if(Gold == 5) {
		s = "YOU GOT 5 GOLD YOU WIN";
	} else {
		s = "THEY GOT 5 GOLD YOU LOSE";
	}

	tinygl_text(s);
	TCNT1 = 0;
	while(1) {
		
		
		navswitch_update ();
		tinygl_update();
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		    break;
		}
	}
	return 1;
}
