/* 
 * File:   fsm.h
 * Author: admin
 *
 * Created on November 16, 2014, 5:24 PM
 */

#ifndef FSM_H
#define	FSM_H

#define TIME_PRESS_MS	5
#define TIME_OFF_MS		10

#define START 			0
#define STAGE_L0		1
#define STAGE_H0		2
#define STAGE_L1		3
#define STAGE_H1		4
#define STAGE_L2		5
#define STAGE_PRE_OFF	6

void fsm(int butnum, int *time_press, int *time_off, int *state, int *lamp_stat);

#endif	/* FSM_H */

