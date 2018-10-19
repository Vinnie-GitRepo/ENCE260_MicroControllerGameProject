/***********************************************************************
# File:          NavswitchSelections.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module handling the navswitch controlling in our game
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "system.h"
#include "pacer.h"
#include "ir_uart.h"
#include "navswitch.h"
#include "tinygl.h"
#include "Animations.h"
#include "Tables.h"


/*
 * Handles the in-game player choices made via the nav switch
 */
char getSelectedChar(void)
{
    int navswitchVal = 0;
    char returnChar = 'G';

    while (1) {
        // Wait times for updates
        pacer_wait();
        tinygl_update();
        navswitch_update();
        display_character(returnChar);


        // Navswitch option selections, in order G, S, T, G, ...
        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            navswitchVal = (navswitchVal + 1) % 3;
        }

        // Navswitch option selections, in order G, T, S, G, ...
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            navswitchVal = (navswitchVal - 1) % 3;
            if (navswitchVal == -1) {
                navswitchVal = 2;
            }
        }

        // Sets the selected letter upon pressing, clearing the board
        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ClearBoard();
            tinygl_clear();
            tinygl_update();
            break;
        }

        returnChar = GetGTS(navswitchVal);
    }

    return returnChar;
}


