/***********************************************************************
# File:          GTS.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for our assignment's Gold Trap Steal game
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
#include "NavswitchSelections.h"
#include "Starter.h"

#define PACER_RATE 3000
#define OPPONENT_TRAPPED 3
#define PLAYER_TRAPPED -1
#define WAIT_TIME 50

/*
 * What runs the game
 */
int GTS_Game(void)
{
    char Gold = '0';
    char OtherGold = '0';

    // Start timers. Well mainly TCNT1
    TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;

    // The RPS character that displays on the LED screen while also being what is sent to the other UCFK4
    char character = 'G';

    // The char that waits for then holds the character sent by the other UCFK4
    char receivedCharacter = '0';

    // 1 is if this UCFK4 outCome and if it ends with 0, then UCFK4 lost
    int outCome = 0;

    // 0 if the isAnimating is still going, 1 for when it finishes
    int isAnimating = 0;

    // Starts up the infrared reader and sender
    ir_uart_init();

    navswitch_init();
    pacer_init(PACER_RATE);


    //
    while ((outCome != PLAYER_TRAPPED) && (outCome != OPPONENT_TRAPPED) && (Gold < '5') && (OtherGold < '5')) {
        // System initialised
        system_init();

        // Sets the waiting time for anything tinygl related
        OneText_init();

        character = 'G';
        outCome = 5;
        character = getSelectedChar();
        isAnimating = 0;
        receivedCharacter = '0';














        // Return received character after the loop breaks

        // Waits for the letter from the other UCFK4 to be sent while also sending its own letter
        TCNT1 = 0;
        while (1) {
            // Playing the cool isAnimating for the lock in
            while (!isAnimating) {
                isAnimating = RollFillGTS();
            }

            // The real start to the previous while loop
            tinygl_update();

            if (ir_uart_read_ready_p()) {
                receivedCharacter = ir_uart_getc();
            }

            // This checks if the letter has been received and if it is of the correct type
            // Also for later it checks if you both got the same thing
            if ((receivedCharacter == 'G' || receivedCharacter == 'T' || receivedCharacter == 'S') && TCNT1 > WAIT_TIME)  {
                ir_uart_putc(character);
                ClearBoard();
                tinygl_clear();
                tinygl_update();
                RollDel();
                break;
            }

            navswitch_update();

            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ir_uart_putc(character);
            }
        }

        // This is all for setting up and checking who outCome
        // printing out either 'W' or 'L'
        ClearBoard();
        tinygl_clear();
        tinygl_update();
        RollDel();
        outCome = determineRoundOutcome(character, receivedCharacter);
		// If you got trapped or trapped the other player the game ends here.
        if(outCome == OPPONENT_TRAPPED || outCome == PLAYER_TRAPPED) {
             break;
        }

		// Puts up gold if you picked gold. Does the same for your tally of the other persons gold.
        if(character == 'G') {
            Gold += 1;
        }
        if(receivedCharacter == 'G') {
            OtherGold += 1;
        }






        // This loop just needs to be there for the messages to play there full way through
        isAnimating = 0;

        // Can make this run with a bool that gets ended by the below break conditional (that will change)
        while (1) {



            while (!isAnimating) {
                isAnimating = RollFillGTS();
                if ((outCome == PLAYER_TRAPPED) || (outCome == OPPONENT_TRAPPED)) {
                    ClearBoard();
                    tinygl_clear();
                    break;
                }

                TCNT1 = 0;
            }




            // COULD BREAK THIS INTO A FUNCTION RETURNING OTHERGOLD

            // The real start to the previous while loop
            tinygl_update();
            OtherGold = ' ';
            while (1) {
                navswitch_update();
                tinygl_update();

                if (ir_uart_read_ready_p()) {
                    OtherGold = ir_uart_getc();
                }

                if ((OtherGold >= '0' && OtherGold < '6') && TCNT1 > WAIT_TIME) {
                    ir_uart_putc(Gold);
                    ClearBoard();
                    tinygl_clear();
                    tinygl_update();
                    RollDel();
                    TCNT1 = 50;
                    break;
                }

                if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                    ir_uart_putc(Gold);
                }
            }



            if (receivedCharacter == 'S' && character != 'S') {
                OtherGold += CheapInt(Gold);
                Gold = '0';
            } else if (character == 'S' && receivedCharacter != 'S'){
                Gold += CheapInt(OtherGold);
                OtherGold = '0';
            }

            // This checks if the letter has been resived and if it is of the correct type.
            // Also for later it checks if you both got the same thing */
            isAnimating = 0;
            navswitch_update();
            while (!isAnimating){
                isAnimating = DisplayGold(Gold);
            }

            break;
        }



        ClearBoard();

    }




    isAnimating = 0;
    while(!isAnimating) {
        isAnimating = DisplayWinnerGTS(outCome, Gold, OtherGold);
    }
    return 1;
}
