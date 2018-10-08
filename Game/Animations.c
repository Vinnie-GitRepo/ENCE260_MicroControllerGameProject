#include "Animations.h"
#include "pio.h"
#include "system.h"

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

int FillBoard(void)
{
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	TCCR1C = 0x00;
	system_init ();
	ConfigBoard();
	int Timer = 0;	
	while (TCNT1 < 1400)
	{
		
		if(TCNT1 < 1000 && Timer < 1) {
			pio_output_low(LEDMAT_ROW1_PIO);
			pio_output_low(LEDMAT_COL1_PIO);
			TCNT1 = 0; 
			Timer += 1;
		} 
		if(TCNT1 > 1050 && Timer < 2) {
			pio_output_low(LEDMAT_COL2_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1100 && Timer < 3) {
			pio_output_low(LEDMAT_COL3_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1150 && Timer < 4) {
			pio_output_low(LEDMAT_COL4_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1200 && Timer < 5) {
			pio_output_low(LEDMAT_COL5_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1225 && Timer < 6) {
			pio_output_low(LEDMAT_ROW2_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1250 && Timer < 7) {
			pio_output_low(LEDMAT_ROW3_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1275 && Timer < 8) {
			pio_output_low(LEDMAT_ROW4_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1300 && Timer < 9) {
			pio_output_low(LEDMAT_ROW5_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1325 && Timer < 10) {
			pio_output_low(LEDMAT_ROW6_PIO);
			TCNT1 = 0;
			Timer += 1;
		}
		if(TCNT1 > 1350 && Timer < 11) {
			pio_output_low(LEDMAT_ROW7_PIO);
			TCNT1 = 0;
			Timer += 1;
			return 1;
		}

	}

}

