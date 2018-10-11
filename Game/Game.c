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

/* makes sure the right character is displayed through a buffer.
Also puts the null byte of '\0'to show the end of a display_character */
void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


/* What runs the game */
int main (void)
{
    char Wins = '0';
    char Loses = '0';

	/* Start timers. Well mainly TCNT1 */
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	TCCR1C = 0x00;	

    /* The RPS character that displays on the LED screen while also being what is sent to the other UCFK4 */
    char character = 'R';

    /* The char that waits for then holds the character sent by the other UCFK4 */
    char receivedCharacter = '0';

    /* 1 is if this UCFK4 won and if it ends with 0, then UCFK4 lost */
    int Won = 0;

    /* 0 if the isAnimating is still going, 1 for when it finishes*/
    int isAnimating = 0;

    /* Starts up the infer red reader and sender */
    ir_uart_init();

    

    navswitch_init ();
    int NavSwitch_Val = 0;

    pacer_init (PACER_RATE);
	while(Wins != '5' && Loses != '5')
	{
		/* System inilzeed */
    	system_init ();		
		
		/* Sets the waiting time for anything tinygl related */
		OneText_init();

		NavSwitch_Val = 0;
		character = 'R';
		/*While loop that will stop when you select rock, paper or scissors (R, P or S) through pushing down the navswitch */
		while (1)
		{
			PORTC |=(1 <<2);
		    /*Wait times for things to update */
		    pacer_wait ();
		    tinygl_update ();
		    navswitch_update ();
		    display_character (character);
		    /* setting up to go up characters and down to go down characters */
		    if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
		        NavSwitch_Val = (NavSwitch_Val + 1)%3;

		    }
		    if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
		        NavSwitch_Val = (NavSwitch_Val - 1)%3;
		        if(NavSwitch_Val == 0) {
		            NavSwitch_Val = 3;
		        }
		    }

		/* This locsk in the letter picked and clears the board from all presets for the isAnimatings */
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		    ClearBoard();
		    tinygl_clear();
		    tinygl_update ();
		    break;
		}
		/* gets the character corrsponding to the value */
		character = GetPSR(NavSwitch_Val);
		isAnimating = 0;



		}
		receivedCharacter = '0';
		/* waits for the letter from the other UCFK4 to be sent while also sending it's own letter */
		while(1) {
		    /* Playing the cool isAnimating for the lock in */
		    while(isAnimating == 0) {
		        isAnimating = RollFill();
		    }

		    /*The real start to the previous while loop */

		    tinygl_update();

		    

		    if(ir_uart_read_ready_p()) {
		        receivedCharacter = ir_uart_getc();
		    }
		    /* This checks if the letter has been resived and if it is of the correct type.
		    Also for later it checks if you both got the same thing */
		    if (receivedCharacter == 'R' || receivedCharacter == 'S' || receivedCharacter == 'P')  {
		        ir_uart_putc(character);
		        ClearBoard();
		    	tinygl_clear();
		        tinygl_update();
				RollDel();
		        break;
		    }


		    navswitch_update ();
		    if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
		        ir_uart_putc(character);
				ClearBoard();
		    	tinygl_clear();
		        tinygl_update();
				RollDel();
				/* Testing */break;
		    }
		}

		/*This is all for setting up and checking who won.
		printing out either 'W' or 'L' */
		Won = WhoWon(character, receivedCharacter);
		if(Won == 1) {
			character = 'W';
			Wins += 1;
		} else if(Won == 0) {
			character = 'L';
			Loses += 1;
		} else {
			character = 'D';
		}

		/* Resetting Timer */
		
		TCNT1 = 0;
		/* This loop just needs to be there for the messages to play there full way through. */
		while(TCNT1 < 24000) {
			
			
		    tinygl_update();
			display_character (character);
		}
		ClearBoard();
		isAnimating = 0;
		while(isAnimating == 0) {
			isAnimating = DisplayScores(Wins, Loses);
		}
		

	}
	isAnimating = 0;
	while(isAnimating == 0) {
			isAnimating = DisplayWinner(Wins, Loses);
	}
    return 0;
}
