/*
# File:   Animations.c
# Author: Group417
# Date:   11 OCT 2018
# Descr:  Animations on the LED board

LetterPicker.o */

#include "LetterPicker.h"
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "pio.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_2.h"
#include "Starter.h"

#define LOOP_RATE 500
#define PACER_RATE 3000
#define PACER_RATE_SCROLL 500
#define MESSAGE_RATE 100
#define MESSAGE_RATE_SCROLL 1
#define PACER_RATE_MENU 500
#define MESSAGE_RATE_MENU 3

/* Sets up tinygl and pacer for when it's displaying one character rather then a message */
void OneText_init(void)
{
	pacer_init (PACER_RATE);
	tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_2);
    tinygl_text_speed_set (MESSAGE_RATE);
	tinygl_text_dir_set (0);
}

/* Sets up tinygl and pacer for the text that displays on the menu*/
void MenuText_init(void)
{
	pacer_init (PACER_RATE_MENU);
	tinygl_init (PACER_RATE_MENU);
	tinygl_font_set (&font3x5_1);
	tinygl_text_dir_set (1);
	tinygl_text_speed_set (MESSAGE_RATE_MENU);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/* Sets up tinygl and pacer for any scorlling text other then menu*/
void ScrollText_init(void)
{
	pacer_init (PACER_RATE_SCROLL);
	tinygl_init (PACER_RATE_SCROLL);
	tinygl_font_set (&font3x5_1);
	tinygl_text_dir_set (1);
	tinygl_text_speed_set (MESSAGE_RATE_SCROLL);
	tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
}

/* Sets up pio so it's easy to manipulate */
void PioBroad_init(void)
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
