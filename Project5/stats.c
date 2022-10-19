/*
 * COMP3500: Project 5 Scheduling
 * Mary Mitchell
 * Due Date: 04/25/2022
 *
 * stats.c: includes definitions that implement calculations for scheduling statistics
 *
 * How to compile?
 * gcc -c stats.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"

/*
 * Takes an array of finished tasks and its length as parameters.
 * Goes through the array and calculate the average waiting time
 * for the tasks after going through a scheduling policy.
 */
double avg_waiting_time(task_t finished_tasks[], u_int count) {
    double wait_time = 0;
    double out_wait_time = 0;
    int i; 
    // wait time = end time - arrival time - burst time
    for(i = 0; i < count; i++) {
        wait_time = finished_tasks[i].end_time - finished_tasks[i].arrival_time - finished_tasks[i].burst_time;
        out_wait_time += wait_time;
    }
    out_wait_time /= count;
    return out_wait_time;
}

/*
 * Takes an array of finished tasks and its length as paramters.
 * Goes through the array and calculates the average response time
 * for the tasks after going through a scheduling policy.
 */
double avg_response_time(task_t finished_tasks[], u_int count) {
    double response_time = 0;
    double out_response_time = 0;
    int i; 
    // response time = start time - arrival time
    for(i = 0; i < count; i++) {
        response_time = finished_tasks[i].start_time - finished_tasks[i].arrival_time;
        out_response_time += response_time;
    }
    out_response_time /= count;
    return out_response_time;
}

/*
 * Takes an array of finished tasks and its length as parameters.
 * Goes through the array and calculates the average turnaround time 
 * for the tasks after going through a scheduling policy.
 */
double avg_turnaround_time(task_t finished_tasks[], u_int count) {
    double turnaround_time = 0;
    double out_turnaround_time = 0;
    int i; 
    // turnaround time = end time - arrival time
    for(i = 0; i < count; i++) {
        turnaround_time = finished_tasks[i].end_time - finished_tasks[i].arrival_time;
        out_turnaround_time += turnaround_time;
    }
    out_turnaround_time /= count;
    return out_turnaround_time;
}

/*
 * Takes an array of finished tasks and its length as parameters.
 * Goes through the array and calculates the average cpu usage time
 * after going through a scheduling policy.
 */
double avg_cpu_time(task_t finished_tasks[], u_int count) {
    double cpu_time = 0;
    double out_cpu_time = 0;
    double total_time = 0;
    int i; 
    // cpu time = total burst time / total time 
    for(i = 0; i < count; i++) {
        cpu_time = finished_tasks[i].burst_time;
        out_cpu_time += cpu_time;
    }
    int j;
    for(j = 0; j < count; j++) {
        if(finished_tasks[j].end_time > total_time) {
            total_time = finished_tasks[j].end_time;
        }
    }
    out_cpu_time /= total_time;
    out_cpu_time = out_cpu_time * 100;
    return out_cpu_time;
}

/*
 * Prints out all of the stats.
 */ 
void print_stats(task_t finished_tasks[], u_int count) {
    double waiting = avg_waiting_time(finished_tasks, count);
	double response = avg_response_time(finished_tasks, count);
	double turnaround = avg_turnaround_time(finished_tasks, count);
	double cpu = avg_cpu_time(finished_tasks, count);
    printf("Average waiting time:    %.2f\n", waiting);
	printf("Average response time:   %.2f\n", response);
	printf("Average turnaround time: %.2f\n", turnaround);
	printf("Overall CPU usage:       %.2f%\n", cpu);
}
