/*
 * COMP 3500: Project 5 Scheduling
 * Xiao Qin
 * Version 1.0  11/18/2019
 *
 * Modified by: Mary Mitchell
 * Due Date: 04/25/2022
 *
 * This source code shows how to conduct separate compilation.
 *
 * How to compile using Makefile?
 * $make
 *
 * How to manually compile?
 * $gcc -c open.c
 * $gcc -c read.c
 * $gcc -c print.c
 * $gcc -c policies.c
 * $gcc -c stats.c
 * $gcc open.o read.o print.o policies.o stats.o scheduler.c -o scheduler
 *
 * How to run?
 * Case 1: no argument. Sample usage is printed
 * $./scheduler
 * Usage: scheduler <file_name>
 *
 * Case 2: file doesn't exist.
 * $./scheduler file1
 * File "file1" doesn't exist. Please try again...
 *
 * Case 3: Input file
 * $./scheduler task.list [FCFS|RR [time_quantum]|SRTF]
 * data in task.list is printed below...
 *
 * Sources: I used the materials from Canvas and lectures to complete this. I also consulted stackoverflow
 * to determine error messages and warnings. The command line parser is based on input.c and command.c 
 *
 * DISCLAIMER: RR policy won't run. Program doesn't crash but it 
 * won't stop. Must use ctr+c to stop program. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"
#include "print.h"
#include "open.h"
#include "read.h"
#include "policies.h"
#include "stats.h"

int main( int argc, char *argv[] )  {
 
    char *file_name; /* file name from the commandline */
 
    FILE *fp; /* file descriptor */
 
    task_t task_array[MAX_TASK_NUM];
    task_t stat_array[MAX_TASK_NUM];

    int error_code;
    u_int i;
    u_int count;
    u_int time_quantum = 0;
    
    // Make sure there are a proper number of arguments passed
    if(argc < 3 || argc > 4) {
 	printf("Usage: input <file_name>\n");
	return EXIT_FAILURE;
    }

    // If you try the RR policy make sure to get the time quantum
        if(strcmp(argv[2], "RR") == 0) {
	if(argc == 4) {
		printf("Time quantum is set to: %s\n", argv[3]);
		time_quantum = atoi(argv[3]);
	} else {
		printf("You must enter a time quantum for the RR policy\n");
		return EXIT_FAILURE;
	}
    }

    // Get information from the file   
    error_code = open_file(argv[1], &fp);
    if (error_code == 1)
        return EXIT_FAILURE;
 
    printf("Scheduling Policy: %s\n", argv[2]);

    read_file(fp, task_array, &count);
    print_task_list(task_array, count);

	printf("==================================================================\n");
        
        // Determine which policy to go to	
   	if(strcmp(argv[2], "FCFS") == 0) {
		fcfs(task_array, count, stat_array);
	} else if(strcmp(argv[2], "RR") == 0) {
		if(time_quantum <= 0) {
			printf("Error! Time quantum must be greater than 0.\n");
			return EXIT_FAILURE;
		}
		rr(task_array, count, time_quantum, stat_array);
	} else if(strcmp(argv[2], "SRTF") == 0) {
		srtf(task_array, count, stat_array);
	} else {
		printf("Invalid policy.\n");
		return 0;
	}
 
        // Once a policy has been implemented, calculate and print statistics
	printf("==================================================================\n");
	print_stats(stat_array, count);
	printf("==================================================================\n");
 	
	fclose(fp);

    return EXIT_SUCCESS;
}
