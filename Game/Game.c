/***********************************************************************
# File:          Game.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   The main game file for this assignment
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "Tables.h"
#include "Animations.h"
#include "LetterPicker.h"
#include "Starter.h"
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
    int isAnimating = 0;
    

    while (1) {
	tinygl_text(" GOLD TRAP STEAL!");
	isAnimating = 0;
	game_running = 0;
        while (1) {
            game_running = 0;
            tinygl_update();
            navswitch_update();

            // This locks in the letter picked and clears the board from all presets for the isAnimatings
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                tinygl_clear();
                break;
            }
        }
        while(!isAnimating) {
        isAnimating = DisplayInfo();
        }


        while (!game_running) {
            game_running = GTS_Game();
        }

    }
}
