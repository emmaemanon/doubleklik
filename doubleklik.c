// ------- Preamble -------- //
#include <stdio.h>
#include <avr/io.h> /* Defines pins, ports, etc */
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h> /* Functions to waste time */
#include "uart/uart.h"

#include "fsm.h"

uint8_t sys_state = START;

uint16_t time_press = TIME_PRESS_MS;
uint16_t time_off = TIME_OFF_MS;
uint16_t time_debounce = TIME_DEBOUNCE_US;

uint8_t lamp_stat = 0;

uint8_t butnum = 0;

uint8_t debounce_button(void) {
	if ((PINBUTTON & (1 << PN_BUTTON)) == 0) {
		_delay_us(TIME_DEBOUNCE_US);
		if ((PINBUTTON & (1 << PN_BUTTON)) == 0) {
			return (1);
		}
	}
	return (0);
}

void set_lamp(void) {
	if (lamp_stat == 1) {
		PRTLED_LAMP |= (1 << PN_LED_LAMP);
	}
	else
	{
		PRTLED_LAMP &= ~(1 << PN_LED_LAMP);
	}
}

int main(void) {
	char serial_buffer[100];
	
	DDRLED_LAMP |= (1 << PN_LED_LAMP);
	
	DDRBUTTON &= ~(1 << PN_BUTTON);
	PRTBUTTON |= (1 << PN_BUTTON);
	
	// set up timer 0 for 1 mSec ticks
	TIMSK2 = (1<<OCIE2A); // turn on timer 0 cmp match ISR
	OCR2A = 249; // set the compare reg to 250 time ticks
	TCCR2A = (1<<WGM21); // turn on clear-on-match
	TCCR2B = (1<<CS22) | (0<<CS21) | (0<<CS20);	// clock prescalar to 64
	
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	sei(); // serial library Fleury harus pakai interrupt
	
	// ------ Event loop ------ //
	while (1) {
		butnum = debounce_button();
		fsm(&butnum, &time_press, &time_off, &sys_state, &lamp_stat);
		
		set_lamp();
		// Serial Untuk Debugging
		sprintf(serial_buffer, "butnum %d | time_press %d | time off %2d | lamp %d state %d", butnum, (unsigned)time_press, (unsigned)time_off, lamp_stat, sys_state);
		uart_puts(serial_buffer);
		uart_puts("\r\n");
		_delay_ms(1); /* wait */
	} /* End event loop */
	
	return (0); /* This line is never reached */
}


ISR(TIMER2_COMPA_vect) {
	// decrement debouncing task time
	if (time_press > 0) {
		time_press--;
	}
	if (time_off > 0) {
		time_off--;
	}
	// if (time_debounce > 0) {
		// time_debounce--;
	// }
}