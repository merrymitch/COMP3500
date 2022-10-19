/*
 * COMP 3500: Project 5 Scheduling
 * Mary Mitchell
 * Version 1.0  04/25/2022
 * 
 * Completed by: Mary Mitchell
 * Due date: 04/25/2022
 *
 * This source code shows how to conduct separate compilation.
 *
 * stats.h: The header file of stats.c
 */

#ifndef _STATS_H_
#define _STATS_H_

/* Method Declarations for Stats Calculations */
double avg_waiting_time(task_t finished_tasks[], u_int count);

double avg_response_time(task_t finished_tasks[], u_int count);

double avg_turnaround_time(task_t finished_tasks[], u_int count);

double avg_cpu_time(task_t finished_tasks[], u_int count);

void print_stats(task_t finished_tasks[], u_int count);

#endif
