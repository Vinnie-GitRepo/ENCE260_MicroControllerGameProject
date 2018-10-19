/***********************************************************************
# File:          LetterPicker.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for our assignment's text processing
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "tinygl.h"
#include "pio.h"
#include "Tables.h"
#include "Animations.h"
#include "Starter.h"
#include "LetterPicker.h"


/*
 * Displays insturctions
 */
int displayInfo(void)
{
    system_init();
    MenuText_init();

    char s[] = "IF ALL LEDS OR TEXT PUSH DOWN NAV";
    char Free_Space[] = " ";
    int Loop = 0;
    tinygl_text(s);
    TCNT1 = 0;
    while (1) {
        if(TCNT1 > 62000) {
            Loop += 1;
            TCNT1 = 0;
        }
        if(Loop >= 6) {
            fillBoard();
            if(Loop == 6) {
                tinygl_text(Free_Space);
                Loop += 1;
            }
        }
        tinygl_update();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            break;
        }
    }
    clearBoard();
    return 1;
}



/*
 * Displays the Gold total until navsiwtch is pushed
 */
int displayGold(char gold)
{
    system_init();
    OneText_init();

    TCNT1 = 0;
    while (1) {
        if (TCNT1 < 10000) {
            displayCharacter('G');
        } else if (TCNT1 > 10000 && TCNT1 < 30000) {
            displayCharacter(gold);
        } else {
            TCNT1 = 0;
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
 * Displays winners of GTS and the type of victory/loss it was
 */
int displayWinner(char wins, char playerGold, char opponentGold)
{
    system_init();

    char* s;
    ScrollText_init();
    s = "inviald End Game";
    if (wins == 3) {
        s = "YOU TRAPPED THEM YOU WIN";
    } else if (wins == -1){
        s = "YOU GOT TRAPPED YOU LOSE";
    } else if (playerGold >= '5') {
        s = "YOU GOT 5 GOLD YOU WIN";
    } else if (opponentGold >= '5'){
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
