/* 
 * File:   main.c
 * Author: sangkuriang
 * Software penguji FSM debouncer
 * Created on November 14, 2014, 2:17 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "fsm.h"

int main(int argc, char** argv) {
    int jumlah_error=0;
    int baris_counter = 0;
    char buffer[1024];
	
    char *filename = "scenario5.csv";//"../test2.csv";
    FILE *f;
    f = fopen(filename, "r");
	
	int last_input = 0;
	int butnum = 0; // parameter untuk FSM
	int state = 0;
	int lamp_stat = 0;
	
	int time_press = TIME_PRESS_MS;
	int time_off = TIME_OFF_MS;


    for (; !feof(f);) {

        char * hasil;
        baris_counter++;
        hasil = fgets(buffer, 1024, f); // ambil 1 baris dari textfile
        if (hasil != NULL) {
            int kolom1;
            // int kolom2;
            //            printf("baris %d %s", baris_counter, buffer);
            // parsing barisnya untuk mendapatkan data per kolom
            sscanf(buffer, "%d", &kolom1);
//            printf("baris %3d %d %d\n", baris_counter, kolom1, kolom2);
            //panggil FSMnya
            {
                butnum = kolom1;
                fsm(butnum, &time_press, &time_off, &state, &lamp_stat);
                printf("baris %3d butnum %d | time_press %d | time off %2d | lamp %d state %d", baris_counter, butnum, time_press, time_off, lamp_stat, state);
                // if (lamp_stat != kolom2) {
                    // printf(" error");
                    // jumlah_error++;
                // }
                printf("\n");
            }
        }
		if (time_press > 0) {
			time_press--;
		}
		if (time_off > 0) {
			time_off--;
		}
    }
    // printf("jumlah error:%d\n",jumlah_error);   // seharusnya jumlah error adalah 0
    return (EXIT_SUCCESS);
}

/*
 * 
 */
// int main(int argc, char** argv) {
    // test_fsm("../test2.csv"); // uji dengan file CSV dengan pola input tertentu
    // return (EXIT_SUCCESS);
// }

