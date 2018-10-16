/***********************************************************************
# File:          GTS.c
# Group:         417
# Authors:       Robert Condon, Vinnie Jamieson
# Description:   Module for our assignment's Gold Trap Steal game
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

#define PACER_RATE 3000
#define MESSAGE_RATE 200




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

    // 1 is if this UCFK4 won and if it ends with 0, then UCFK4 lost
    int Won = 0;

    // 0 if the isAnimating is still going, 1 for when it finishes
    int isAnimating = 0;

    // Starts up the infrared reader and sender
    ir_uart_init();



    navswitch_init();
    int navswitch_val = 0;

    pacer_init(PACER_RATE);
    while ((Won != -1) && (Won != 3) && (Gold < '5') && (OtherGold < '5')) {
        // System initialised
        system_init();

        // Sets the waiting time for anything tinygl related
        OneText_init();

        navswitch_val = 0;
        character = 'G';
        Won = 5;

        // While loop that will stop when you select rock, paper or scissors (R, P or S) through pushing down the navswitch
        while (1)
        {
            // Wait times for things to update
            pacer_wait();
            tinygl_update();
            navswitch_update();
            display_character(character);

            // setting up to go up characters and down to go down characters
            if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
                navswitch_val = (navswitch_val + 1) % 3;

            }

            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                navswitch_val = (navswitch_val - 1) % 3;
                if(navswitch_val == 0) {
                    navswitch_val = 3;
                }
            }

            // This locsk in the letter picked and clears the board from all presets for the isAnimatings
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                ClearBoard();
                tinygl_clear();
                tinygl_update();
                break;
            }

            // gets the character corrsponding to the value
            character = GetGTS(navswitch_val);
        }

        isAnimating = 0;
        receivedCharacter = '0';

        // waits for the letter from the other UCFK4 to be sent while also sending it's own letter
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

            // This checks if the letter has been resived and if it is of the correct type
            // Also for later it checks if you both got the same thing
            if ((receivedCharacter == 'G' || receivedCharacter == 'T' || receivedCharacter == 'S') && TCNT1 > 5)  {
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

                /* Testing
                break;*/
            }
        }

        // This is all for setting up and checking who won
        // printing out either 'W' or 'L'
        ClearBoard();
        tinygl_clear();
        tinygl_update();
        RollDel();
        Won = RoundEnd(character, receivedCharacter);
        if(character == 'G') {
            Gold += 1;
        }
        if(receivedCharacter == 'G') {
            OtherGold += 1;
        }

        // Resetting Timer

        // This loop just needs to be there for the messages to play there full way through
        isAnimating = 0;

        while (1) {
            while (!isAnimating) {
                isAnimating = RollFillGTS();
                if ((Won == -1) || (Won == 3)) {
                    ClearBoard();
                    tinygl_clear();
                    break;
                }

                TCNT1 = 0;
            }
			if ((Won == -1) || (Won == 3)) {
                    ClearBoard();
                    tinygl_clear();
                    break;
             }

            // The real start to the previous while loop
            tinygl_update();
            OtherGold = ' ';
            while (1) {
                PORTC |= (1 << 2);
                navswitch_update();
                tinygl_update();

                if (ir_uart_read_ready_p()) {
                    OtherGold = ir_uart_getc();
                }
				


                if ((OtherGold >= '0' && OtherGold < '6') && TCNT1 > 50)  {
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

            PORTC &= ~(1 <<2);
            ir_uart_putc(Gold);

			if(receivedCharacter == 'S' && character != 'S') {
				OtherGold += CheapInt(Gold);
				Gold = '0';
				
			} else if(character == 'S' && receivedCharacter != 'S'){
				Gold += CheapInt(OtherGold);
				OtherGold = '0';
				/*PORTC &= ~(1 <<2);*/
			}
	    /* This checks if the letter has been resived and if it is of the correct type.
	    Also for later it checks if you both got the same thing */
			isAnimating = 0;
			
		    while (isAnimating == 0){
			isAnimating = DisplayGold(Gold);
		    }

	    break;


        }

        if ((Won == -1) || (Won == 3)) {
            ClearBoard();
            tinygl_clear();
            break;
        }

        ClearBoard();

    }

    isAnimating = 0;
    while(!isAnimating) {
            isAnimating = DisplayWinnerGTS(Won, Gold, OtherGold);
    }
    return 1;
}
