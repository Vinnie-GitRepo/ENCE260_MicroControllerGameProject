# File:           Makefile
# Group:          417
# Authors:        Robert Condon (rtc33), Vinnie Jamieson (vjj14)
# Description:    Makefile for our game assignment
# Last Modified:  18 OCT 2018


# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I../../../drivers -I../../../fonts -I../../../drivers/avr -I../../../utils
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: Game.out


# Compile: create object files from C source files.
Game.o: Game.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/navswitch.h ../../../utils/pacer.h ../../../utils/tinygl.h 
	$(CC) -c $(CFLAGS) $< -o $@

ir_uart.o: ../../../drivers/avr/ir_uart.c ../../../drivers/avr/ir_uart.h ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/avr/timer0.h ../../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../../drivers/avr/pio.c ../../../drivers/avr/pio.h ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../../drivers/avr/prescale.c ../../../drivers/avr/prescale.h ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../../drivers/avr/system.c ../../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../../drivers/avr/timer.c ../../../drivers/avr/system.h ../../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../../drivers/avr/timer0.c ../../../drivers/avr/bits.h ../../../drivers/avr/prescale.h ../../../drivers/avr/system.h ../../../drivers/avr/timer0.h
	$(CC) -c $(CFLAGS) $< -o $@

usart1.o: ../../../drivers/avr/usart1.c ../../../drivers/avr/system.h ../../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../../drivers/display.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../../drivers/ledmat.c ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../../drivers/navswitch.c ../../../drivers/avr/delay.h ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../../utils/font.c ../../../drivers/avr/system.h ../../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../../utils/pacer.c ../../../drivers/avr/system.h ../../../drivers/avr/timer.h ../../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../../utils/tinygl.c ../../../drivers/avr/system.h ../../../drivers/display.h ../../../utils/font.h ../../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

Tables.o: Tables.c Tables.h ../../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

Animations.o: Animations.c Animations.h  ../../../drivers/avr/pio.h ../../../drivers/avr/system.h ../../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

LetterPicker.o: LetterPicker.c LetterPicker.h  ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/navswitch.h ../../../utils/pacer.h ../../../utils/tinygl.h ../../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

Starter.o: Starter.c Starter.h  ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/navswitch.h ../../../fonts/font5x7_1.h ../../../utils/font.h ../../../utils/pacer.h ../../../utils/tinygl.h ../../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

NavswitchSelections.o: NavswitchSelections.c NavswitchSelections.h ../../../drivers/avr/system.h ../../../drivers/navswitch.h ../../../utils/tinygl.h ../../../drivers/avr/ir_uart.h ../../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

GTS.o: GTS.c GTS.h ../../../drivers/avr/ir_uart.h ../../../drivers/avr/system.h ../../../drivers/display.h ../../../drivers/navswitch.h ../../../fonts/font5x7_1.h ../../../utils/font.h ../../../utils/pacer.h ../../../utils/tinygl.h ../../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
Game.out: Game.o ir_uart.o pio.o prescale.o system.o timer.o timer0.o usart1.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o Tables.o Animations.o LetterPicker.o Starter.o GTS.o NavswitchSelections.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: Game.out
	$(OBJCOPY) -O ihex Game.out Game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash Game.hex; dfu-programmer atmega32u2 start
