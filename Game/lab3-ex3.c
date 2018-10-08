#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "Tables.h"
#include "Animations.h"

#define LOOP_RATE 500
#define PACER_RATE 500
#define MESSAGE_RATE 10


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    char character = 'R';
	char Resv = '0';
	int Won = 0;
	int Test = 0;
	ir_uart_init();	
		
    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();

    /* TODO: Initialise IR driver.  */

	int Thing = 0;
    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();
		display_character (character);
        
        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
			
            Thing = (Thing + 1)%3;
		}
        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            Thing = (Thing - 1)%3;
		}
		
		if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
			break;
		}
		
		character = GetPSR(Thing);

        
        
    }
	while(1) {
		while(Test != 1) {
			Test = FillBoard();
		}
		
		
		if(ir_uart_read_ready_p()) {
			Resv = ir_uart_getc();
		}
		ir_uart_putc(character);
		if ((Resv == 'R' || Resv == 'S' || Resv == 'P' )  && Resv != character) {
			ClearBoard();
			tinygl_clear();
			tinygl_update ();
			break;
		}
	}
	Won = WhoWon(character, Resv);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
	tinygl_init (LOOP_RATE);
	tinygl_font_set (&font5x7_1);
	tinygl_text_speed_set (MESSAGE_RATE);
	if(Won == 1) {
			tinygl_text("YOU WON\0");
		} else {
			tinygl_text("YOU LOSE\0");
	}
	while(1) {
		pacer_wait (); 
		tinygl_update();	
	}







    return 0;
}
