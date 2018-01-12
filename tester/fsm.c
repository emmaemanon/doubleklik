#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

// file ini berisi FSM yang akan diuji

/**
 * FSM under test
 * @param input
 * @param state
 * @param output
 */
void fsm(int butnum, int *time_press, int *time_off, int *state, int *lamp_stat) {
    // algoritma FSM di sini
	switch(*state){
		case START:
			*time_press = TIME_PRESS_MS;
			*time_off = TIME_OFF_MS;
			*lamp_stat = 0;
			*state = STAGE_L0;
		break;
		case STAGE_L0: // pushbutton low
			*time_press = TIME_PRESS_MS;
			*time_off = TIME_OFF_MS;
			if (butnum == 1) { *state = STAGE_H0; }
		break;
		case STAGE_H0: // pushbutton high from low
			// time press starts
			*time_off = TIME_OFF_MS;
			if ((*time_press > 0) && (butnum == 0)) { *state = STAGE_L1; }
			else if ((*time_press == 0) && (butnum == 0))
				{ *state = STAGE_PRE_OFF; }
		break;
		case STAGE_L1: // pushbutton low from high
			if ((*time_press > 0) && (butnum == 1)) { *state = STAGE_H1; }
			else if (*time_press == 0) { *state = STAGE_PRE_OFF; }
		break;
		case STAGE_H1: // pushbutton high from low
			*time_off = TIME_OFF_MS;
			if ((*time_press > 0) && (butnum == 0))
				{ *lamp_stat = 1; *state = STAGE_PRE_OFF; }
			else if ((*time_press == 0) && (butnum == 0))
				{ *state = STAGE_PRE_OFF; }
		break;
		// case STAGE_L2: // pushbutton low from high
			
			// *state = STAGE_PRE_OFF;
		// break;
		case STAGE_PRE_OFF: // pushbutton low
			*time_press = TIME_PRESS_MS;
			if (*time_off == 0) { *lamp_stat = 0; *state = STAGE_L0; }
			else if ((*time_off != 0) && (butnum == 1)) { *state = STAGE_H0; }
		break;
		default: break;
	}
}
