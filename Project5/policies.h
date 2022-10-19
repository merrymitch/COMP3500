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
 * policies.h: The header file of policies.c
 */
#ifndef _POLICIES_H_
#define _POLICIES_H_

/* HELPER DEFINITIONS */
/* Determines if task array is empty */
int task_empty(task_t task_array[], u_int count);

/* Determines if ready queue is empty */
int ready_empty(task_t ready_queue[], u_int ready_index);

/* POLICY DEFINITIONS */
/* First Come First Serve */
void fcfs(task_t task_array[], u_int count, task_t finished_tasks[]);

/* Round Robin */
void rr(task_t task_array[], u_int count, u_int time_quantum, task_t finished_tasks[]);

/* Shortest Remaining Time First */
void srtf(task_t task_array[], u_int count, task_t finished_tasks[]);

#endif
