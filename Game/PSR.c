/***********************************************************************
# File:          PSR.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for our assignment's Paper Scissors Rock game
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

#define PACER_RATE 3000
#define MESSAGE_RATE 200


/*
 * What runs the game
 */
int PSR_Game(void)
{
    char Wins = '0';
    char Loses = '0';

    // Start timers. Well mainly TCNT1
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    // The RPS character that displays on the LED screen while also being what is sent to the other UCFK4
    char character = 'R';

    // The char that waits for then holds the character sent by the other UCFK4
    char receivedCharacter = '0';

    // 1 is if this UCFK4 won and if it ends with 0, then UCFK4 lost
    int Won = 0;

    // 0 if the isAnimating is still going, 1 for when it finishes
    int isAnimating = 0;

    // Starts up the infer red reader and sender
    ir_uart_init();

    // Initialises the navigation switch
    navswitch_init();
    int navswitch_val = 0;

    pacer_init(PACER_RATE);
    while (Wins != '3' && Loses != '3')
    {
        // System inilzeed
        system_init();

        // Sets the waiting time for anything tinygl related
        OneText_init();

        navswitch_val = 0;
        character = 'R';

        // While loop that will stop when you select rock, paper or scissors (R, P or S) through pushing down the navswitch
        while (1)
        {
            PORTC |= (1 << 2);

            // Wait times for things to update
            pacer_wait();
            tinygl_update();
            navswitch_update();
            display_character(character);

            // setting up to go up characters and down to go down characters
            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                navswitch_val = (navswitch_val + 1) % 3;
            }

            if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
                navswitch_val = (navswitch_val - 1) % 3;
                if(navswitch_val == 0) {
                    navswitch_val = 3;
                }
            }

            // Sets the selected letter, clearing the board from all presets for the isAnimatings
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ClearBoard();
                tinygl_clear();
                tinygl_update();
                break;
            }

            // gets the character corrsponding to the value
            character = GetPSR(navswitch_val);
        }

        isAnimating = 0;
        receivedCharacter = '0';
        // waits for the letter from the other UCFK4 to be sent while also sending it's own letter

        while (1) {
            // Playing the cool isAnimating for the lock in
            while (!isAnimating) {
                isAnimating = RollFill();
                receivedCharacter = '0';
                TCNT1 = 0;
            }

            // The real start to the previous while loop
            tinygl_update();
            navswitch_update();

            if (ir_uart_read_ready_p()) {
                receivedCharacter = ir_uart_getc();
            }

            // This checks if the letter has been received and if it is of the correct type
            // Also for later it checks if you both got the same thing
            if ((receivedCharacter == 'R' || receivedCharacter == 'S' || receivedCharacter == 'P') && TCNT1 > 200) {
                ir_uart_putc(character);
                ClearBoard();
                tinygl_clear();
                tinygl_update();
                RollDel();
                PORTC &= ~(1 << 2);
                TCNT1 = 50;
                break;
            }

            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
            }

            navswitch_update ();
        }

        // This is all for setting up and checking who won
        // This then prints out either 'W' or 'L'
        Won = DetermineWinner(character, receivedCharacter);
        if (Won == 1) {
            character = 'W';
            Wins += 1;
        } else if (Won == 0) {
            character = 'L';
            Loses += 1;
        } else {
            character = 'D';
        }

        // Resetting Timer
        TCNT1 = 0;

        // This loop just needs to be there for the messages to play there full way through
        while (TCNT1 < 24000) {
            receivedCharacter = 'F';
            tinygl_update();
            display_character(character);
        }

        ClearBoard();
        isAnimating = 0;

        while (!isAnimating) {
            isAnimating = DisplayScores(Wins, Loses);
        }
    }

    isAnimating = 0;
    while (!isAnimating) {
        isAnimating = DisplayWinner(Wins);
    }

    return 1;
}
