/***********************************************************************
# File:          Animations.c
# Group:         417
# Authors:       Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:   Module for LED game animations on the fun kit
# Last Modified: 17 OCT 2018
***********************************************************************/

#include "Animations.h"
#include "pio.h"
#include "tinygl.h"
#include "system.h"

#define PACER_RATE 3000
#define LOOP_RATE 200


/*
 * Configures the board to high for easier manipulation
 */
void configBoard(void)
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



/*
 * Clears the board of any on LEDs.
 */
void clearBoard(void)
{
    configBoard();

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



/*
 * Makes sure the right character is displayed through a buffer.
 * Also puts the null byte of '\0'to show the end of a displayCharacter
 */
void displayCharacter(char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text(buffer);
}



/*
 * Turns all LEDs on the board on.
 */
void fillBoard(void)
{
    configBoard();

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



/*
 * Plays an aniamtion of LED's that fill the board slowly from the
 * top left to bottom right. However, this time is does it faster.
 */
int rollFill(void)
{
    tinygl_init(PACER_RATE);
    tinygl_clear();
    tinygl_point_t pos;

    pos.x = 0;
    pos.y = 0;

    while (1) {
        if (TCNT1 > 300) {
            tinygl_update();
            tinygl_draw_point(pos, 1);
            pos.x += 1;

            if (pos.x == 7) {
                pos.x = 0;
                pos.y += 1;
            }

            TCNT1 = 0;
        }

        if (pos.y == 7) {
            break;
        }
    }

    return 1;
}



/*
 * Ensures that all LEDs are where they were previously.
 */
int rollDel(void)
{
    tinygl_init(PACER_RATE);
    tinygl_clear();
    tinygl_point_t pos;

    pos.x = 0;
    pos.y = 0;

    while (1) {
        tinygl_update();
        tinygl_draw_point(pos, 1);
        pos.x += 1;

        if (pos.x == 7) {
            pos.x = 0;
            pos.y += 1;
        }

        TCNT1 = 0;

        if (pos.y == 8) {
            break;
        }
    }

    tinygl_clear();

    return 1;
}

