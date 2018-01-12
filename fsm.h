/* 
 * File:   fsm.h
 * Author: admin
 *
 * Created on November 16, 2014, 5:24 PM
 */

#ifndef FSM_H
#define	FSM_H


#define DDRLED_LAMP	DDRD
#define PRTLED_LAMP	PORTD
#define PN_LED_LAMP	PD3

#define DDRBUTTON	DDRD
#define PRTBUTTON	PORTD
#define PINBUTTON	PIND
#define PN_BUTTON	PD2

#define TIME_PRESS_MS		1000
#define TIME_OFF_MS			5000
#define TIME_DEBOUNCE_US	1000

#define UART_BAUD_RATE 9600

#define START 			0
#define STAGE_L0		1
#define STAGE_H0		2
#define STAGE_L1		3
#define STAGE_H1		4
#define STAGE_L2		5
#define STAGE_PRE_OFF	6

void fsm(uint8_t *butnum, uint16_t *time_press, uint16_t *time_off, uint8_t *state, uint8_t *lamp_stat);

#endif	/* FSM_H */

