/***********************************************************************
# File:          GTS.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for our assignment's playerGold Trap Steal game
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
* Receives playerGold from the other funkit. Makes sure it passes checks then sends back it's own playerGold.
* Returns the other Funkit's playerGold.
* Takes in the player's playerGold.
*/
char getGold(char playerGold, char opponentGold)
{
    while (1) {
        navswitch_update();
        tinygl_update();

        if (ir_uart_read_ready_p()) {
            opponentGold = ir_uart_getc();
        }

        if ((opponentGold >= '0' && opponentGold < '6') && TCNT1 > WAIT_TIME) {
            ir_uart_putc(playerGold);
            clearBoard();
            tinygl_clear();
            tinygl_update();
            rollDel();
            TCNT1 = 50;
            break;
        }

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(playerGold);
        }
    }
    return opponentGold;

}



/*
* Receives character from the other funkit. Makes sure it passes checks then sends back it's own character.
* Returns the other Funkit's character.
* Takes in the player's character.
*/
char getChar(char character, char receivedCharacter, int isAnimating)
{
    while (1) {
        // Playing the cool isAnimating for the lock in
        while (!isAnimating) {
            isAnimating = rollFill();
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
            clearBoard();
            tinygl_clear();
            tinygl_update();
            rollDel();
            break;
        }

        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
        }
    }
    return receivedCharacter;

}



/*
 * What runs the game
 */
int gameGTS(void)
{
    char playerGold = '0';
    char opponentGold = '0';

    // Start timers. Well mainly TCNT1
    /*TCCR1A = 0x00;
    TCCR1B = 0x05;
    TCCR1C = 0x00;*/

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



    while ((outCome != PLAYER_TRAPPED) && (outCome != OPPONENT_TRAPPED) && (playerGold < '5') && (opponentGold < '5')) {
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
        receivedCharacter = getChar(character, receivedCharacter, isAnimating);


        // This is all for setting up and checking who outCome
        // printing out either 'W' or 'L'
        clearBoard();
        tinygl_clear();
        tinygl_update();
        rollDel();
        outCome = determineRoundOutcome(character, receivedCharacter);

        // If you got trapped or trapped the other player the game ends here.
        if(outCome == OPPONENT_TRAPPED || outCome == PLAYER_TRAPPED) {
             break;
        }

        // Puts up playerGold if you picked playerGold. Does the same for your tally of the other persons playerGold.
        if(character == 'G') {
            playerGold += 1;
        }
        if(receivedCharacter == 'G') {
            opponentGold += 1;
        }

        // This loop just needs to be there for the messages to play there full way through
        isAnimating = 0;

        // Can make this run with a bool that gets ended by the below break conditional (that will change)
        while (1) {
            while (!isAnimating) {
                isAnimating = rollFill();
                TCNT1 = 0;
            }

            // The real start to the previous while loop
            tinygl_update();
            opponentGold = ' ';
            opponentGold = getGold(playerGold, opponentGold);

            if (receivedCharacter == 'S' && character != 'S') {
                opponentGold += charToInt(playerGold);
                playerGold = '0';
            } else if (character == 'S' && receivedCharacter != 'S'){
                playerGold += charToInt(opponentGold);
                opponentGold = '0';
            }

            // This checks if the letter has been resived and if it is of the correct type.
            // Also for later it checks if you both got the same thing */
            isAnimating = 0;
            navswitch_update();
            while (!isAnimating){
                isAnimating = displayGold(playerGold);
            }

            break;
        }

        clearBoard();
    }

    isAnimating = 0;
    while(!isAnimating) {
        isAnimating = displayWinner(outCome, playerGold, opponentGold);
    }

    return 1;
}
