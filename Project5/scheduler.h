/*
 * COMP 3500: Project 5 Scheduling
 * Xiao Qin
 * Version 1.0  11/18/2019
 * 
 * Completed by: Mary Mitchell
 * Due date: 04/25/2022
 *
 * This source code shows how to conduct separate compilation.
 *
 * scheduler.h: The header file of scheduler.c
 */
#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define MAX_TASK_NUM 32

typedef unsigned int u_int;

typedef struct task_info {
    u_int pid;
    u_int arrival_time;
    u_int burst_time;
    /* Add more variables for stat info and array management */
    u_int start_time;
    u_int end_time; 
    u_int wait_time;
    u_int response_time;
    u_int remaining_time;
    u_int ready;
    u_int done;
    u_int current_turn_time;
} task_t;

#endif
