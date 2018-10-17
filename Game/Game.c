/***********************************************************************
# File:          Game.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   The main game file for this assignment
# Last Modified: 17 OCT 2018
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
 * What runs the game
 */
int main(void)
{
    system_init();
    MenuText_init();
    navswitch_init();

    int game_running = 0;
    int Is_animating = 0;
    int navswitch_val = 0;
    tinygl_text(" PAPER SCISSORS ROCK");

    while (1) {
        while (1) {
            game_running = 0;
            tinygl_update();
            navswitch_update();

            // setting up to go up characters and down to go down characters
            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                tinygl_clear();
                navswitch_val = (navswitch_val + 1) % 3;
                GetMenu(navswitch_val);

            }
            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                tinygl_clear();
                navswitch_val = (navswitch_val - 1) % 3;

                if (navswitch_val == 0) {
                    navswitch_val = 3;
                }

                GetMenu(navswitch_val);
            }

            // This locks in the letter picked and clears the board from all presets for the isAnimatings
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                tinygl_clear();
                break;
            }
        }
        while(!Is_animating) {
        Is_animating = DisplayInfo();
        }

        while (navswitch_val == 0 && game_running == 0) {
            game_running = PSR_Game();
        }

        while (navswitch_val == 1 && game_running == 0) {
            game_running = GTS_Game();
        }

        if (navswitch_val == 2) {
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
