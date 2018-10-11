/*
# File:   Animations.c
# Author: Group417
# Date:   10 OCT 2018
# Descr:  Animations on the LED board
*/
#include "Animations.h"
#include "pio.h"
#include "tinygl.h"
#include "system.h"


#define PACER_RATE 3000
#define LOOP_RATE 200


void ConfigBoard(void)
{
	pio_config_set(LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
	pio_config_set(LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);	
	pio_config_set(LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);	
	pio_config_set(LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH); 
	
}

void ClearBoard(void)
{
	ConfigBoard();
	pio_output_high(LEDMAT_ROW1_PIO);
	pio_output_high(LEDMAT_ROW2_PIO);
	pio_output_high(LEDMAT_ROW3_PIO);
	pio_output_high(LEDMAT_ROW4_PIO);
	pio_output_high(LEDMAT_ROW5_PIO);
	pio_output_high(LEDMAT_ROW6_PIO);
	pio_output_high(LEDMAT_ROW7_PIO);	
	pio_output_high(LEDMAT_COL1_PIO);
	pio_output_high(LEDMAT_COL2_PIO);
	pio_output_high(LEDMAT_COL3_PIO);
	pio_output_high(LEDMAT_COL4_PIO);
	pio_output_high(LEDMAT_COL5_PIO);

}

void FillBoard(void)
{
	ConfigBoard();
	pio_output_low(LEDMAT_ROW1_PIO);
	pio_output_low(LEDMAT_ROW2_PIO);
	pio_output_low(LEDMAT_ROW3_PIO);
	pio_output_low(LEDMAT_ROW4_PIO);
	pio_output_low(LEDMAT_ROW5_PIO);
	pio_output_low(LEDMAT_ROW6_PIO);
	pio_output_low(LEDMAT_ROW7_PIO);	
	pio_output_low(LEDMAT_COL1_PIO);
	pio_output_low(LEDMAT_COL2_PIO);
	pio_output_low(LEDMAT_COL3_PIO);
	pio_output_low(LEDMAT_COL4_PIO);
	pio_output_low(LEDMAT_COL5_PIO);
	
}

int RollFill(void)
{
	tinygl_init (PACER_RATE);
	tinygl_clear();
	tinygl_point_t pos;
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	TCCR1C = 0x00;
	pos.x = 0;
	pos.y = 0;
	while (1)
	{
		if(TCNT1 > 500) {
			tinygl_update ();
			tinygl_draw_point (pos, 1); 
			pos.x += 1;
			if(pos.x == 7) {
				pos.x = 0;
				pos.y += 1;
			}
			TCNT1 = 0;
		}
		
		if(pos.y ==  7) {
			break;
		}
	}
	return 1;
}

int RollDel(void)
{
	tinygl_init (PACER_RATE);
	tinygl_clear();
	tinygl_point_t pos;
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	TCCR1C = 0x00;
	pos.x = 0;
	pos.y = 0;
	while (1)
	{
		tinygl_update ();
		tinygl_draw_point (pos, 1); 
		pos.x += 1;
		if(pos.x == 7) {
			pos.x = 0;
			pos.y += 1;
		}
		TCNT1 = 0;
		
		if(pos.y ==  8) {
			break;
		}
	}
	tinygl_clear();
	return 1;

}

