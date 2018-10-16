/***********************************************************************
# File:          Game.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   The main game file for this assignment
# Last Modified: 15 OCT 2018
***********************************************************************/

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
#include "GTS.h"

#define LOOP_RATE 500
#define PACER_RATE 1000
#define MESSAGE_RATE 10


/*
 * Makes sure the right character is displayed through a buffer.
 * Also puts the null byte '\0' to show the end of a display_character.
 */




/*
 * What runs the game
 */
int main(void)
{
    system_init();
    MenuText_init();
    navswitch_init();

    int GameRunning = 0;
    int NavSwitch_Val = 0;
    tinygl_text(" PAPER SCISSORS ROCK");
    //NavSwitch_Val = 0; This shouldn't be necessary but we'll test anyway.
    while(1)
    {
        while (1)
        {
            GameRunning = 0;
            tinygl_update();
            navswitch_update();

            /* setting up to go up characters and down to go down characters */
            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                tinygl_clear();
                NavSwitch_Val = (NavSwitch_Val + 1) % 3;
                GetMenu(NavSwitch_Val);

            }
            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                tinygl_clear();
                NavSwitch_Val = (NavSwitch_Val - 1) % 3;

                if (NavSwitch_Val == 0) {
                    NavSwitch_Val = 3;
                }

                GetMenu(NavSwitch_Val);
            }

            /* This locks in the letter picked and clears the board from all presets for the isAnimatings */
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                tinygl_clear();
                break;
            }
        }

        while (NavSwitch_Val == 0 && GameRunning == 0) {
            GameRunning = PSR_Game();
        }

        while (NavSwitch_Val == 1 && GameRunning == 0) {
            GameRunning = GTS_Game();
        }

        if(NavSwitch_Val == 2) {
            tinygl_text(" WORK IN PROGRESS");
            while (1) {
                navswitch_update();
                tinygl_update();

                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    tinygl_clear();
                    break;
                }
            }
    }
    }

}
