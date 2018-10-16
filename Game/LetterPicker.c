/***********************************************************************
# File:          LetterPicker.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   Module for our assignment's text processing
# Last Modified: 15 OCT 2018
***********************************************************************/

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


/*
 * Displays the scores of wins and loses until navsiwtch is pushed
 */
int DisplayScores(char Wins, char Loses)
{

    system_init();
    ScrollText_init();

    char s[] = { ' ','W', Wins,' ','L', Loses};

    tinygl_text(s);
    TCNT1 = 0;
    while (1) {

        tinygl_update();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
    return 1;
}



/*
 * Displays the Gold total until navsiwtch is pushed
 */
int DisplayGold(char Gold, char OtherGold)
{

    system_init();
    OneText_init();
	TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

	int Go = 0;
    /*char s[] = { ' ','G', 'O', 'L', 'D', ' ', Gold}; */

    
    TCNT1 = 0;
    while (1) {
		if(TCNT1 < 10000) {
			display_character('G');
		}else if(TCNT1 > 10000 && TCNT1 < 30000) {
			display_character(Gold);
		} else {
			display_character(OtherGold);
		}
        tinygl_update();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }

    return 1;
}



/*
 * Displays the scores 'YOU WON' or 'YOU LOST' until navsiwtch is pushed
 */
int DisplayWinner(char Wins)
{

    system_init();
    ScrollText_init();
    char* s;

    if (Wins == '3') {
        s = "YOU WON!";
    } else {
        s = "YOU LOST </3";
    }

    tinygl_text(s);
    TCNT1 = 0;

    while (1) {

        tinygl_update();
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }

    return 1;
}

/*
 * Displays winners of GTS and the type of victory/loss it was
 */
int DisplayWinnerGTS(char Wins, char Gold, char OtherGold)
{

    system_init();

    char* s;
    ScrollText_init();
    if (Wins == 3) {
        s = "YOU TRAPPED THEM YOU WIN";
    } else if (Wins == -1){
        s = "YOU GOT TRAPPED YOU LOSE";
    } else if (Gold >= '5') {
        s = "YOU GOT 5 GOLD YOU WIN";
    } else if (OtherGold >= '5'){
        s = "THEY GOT 5 GOLD YOU LOSE";
    }

    tinygl_text(s);
    TCNT1 = 0;

    while (1) {

        navswitch_update();
        tinygl_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }

    return 1;
}
