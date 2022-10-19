/*
 * COMP3500: Project 5 Scheduling
 * Mary Mitchell
 * Due Date: 04/25/2022
 *
 * policies.c: includes definitions that implement certain scheduling policies
 *
 * How to compile:
 * gcc -c policies.c
 *
 * Sources: I used information from Canvas and from lectures to implement this solution. I also consulted stackoverflow for general information on error messages and warnings. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scheduler.h"

/* POLICY DEFINITIONS */

/*
 * Method definition for first come first serve scheduling policy.
 * Takes the task array, its length, and an empty array as parameters.
 */
void fcfs(task_t task_array[], u_int count, task_t finished_tasks[]) {
	// Initialize some variables to help with the policy
	u_int clock = 0;
	u_int ready_index = 0;
	u_int finished_index = 0;
	int empty_task = 0;
	int empty_ready = 0;
	task_t task;
	task_t ready_queue[count];
		
    // Initialize the variables that describe the state of a task.
	int i;
	for(i = 0; i < count; i++) {
		task_array[i].ready = 0;
		task_array[i].done = 0;
	}

    // The scheduling policy goes until both the task array and ready queue are empty.
	while((empty_task = task_empty(task_array, count)) != 1 || (empty_ready = ready_empty(ready_queue, ready_index)) != 1) {
		// For each task in the task array, determine if it is ready to be be placed in the ready queue.
        int j;
		for(j = 0; j < count; j++) {
			if(task_array[j].arrival_time <= clock && task_array[j].ready == 0) {
				task_array[j].ready = 1; // Mark that it is in the ready queue.
				task_array[j].remaining_time = task_array[j].burst_time;
				ready_queue[ready_index] = task_array[j]; // Put the task in the ready queue.		
				ready_index = ready_index + 1; // Increment the amount of values in the ready queue.		
			}
		}
		
        // Check that the ready queue is not empty before trying to run a task.
		if((empty_ready = ready_empty(ready_queue, ready_index)) != 1) {
            // Go through the ready queue and find the first task that is not done.
			int k;
			int index; // Which element in queue is picked.
			for(k = 0; k < ready_index; k++) {
				if(ready_queue[k].done == 0) {
					task = ready_queue[k];
					index = k;
					break;			
				}
			}
			
            // Set the start time for tasks that have not had any cpu time yet.
			if(task.remaining_time == task.burst_time) {
				task.start_time = clock;
			}
			
			task.remaining_time--; // Decrement the remaining time of the process
			printf("<time %u> process %u is running\n", clock, task.pid);
			clock = clock + 1; // Increment the clock.
			ready_queue[index] = task; // Update the ready queue information
            	
			// Check to see if the process has finished its task.
			if(task.remaining_time == 0) { 
				printf("<time %u> process %u is finished...\n", clock, task.pid);
				task.end_time = clock; // Set the finish time.
				ready_queue[index].done = 1; // "Remove" the task from the ready queue
				finished_tasks[finished_index] = task; // Add the task to the finished tasks.
				finished_index = finished_index + 1; // Increment the amount of finished tasks.		
			}
			
		} else { // If the ready queue is empty, no task is running.
			printf("<time %u> no process is running\n", clock);
			clock = clock + 1; // Increment clock.
		}
		
	}

    printf("<time %u> all processes finished ......\n", clock);

}

/*
 * Method definition for round robin scheduling policy.
 * Takes the task array, its length, a time quantum, and an empty array as parameters.
 */

void rr(task_t task_array[], u_int count, u_int time_quantum, task_t finished_tasks[]) {
	// Initialize some variables to help with the policy.
	u_int clock = 0;
	u_int ready_index = 0;
	u_int finished_index = 0;
	int empty_task = 0;
	int empty_ready = 0;
	task_t task;
	task_t ready_queue[count];
		
    // Initialize the variables that describe the state of a task.
	int i;
	for(i = 0; i < count; i++) {
		task_array[i].ready = 0;
		task_array[i].done = 0;
		task_array[i].current_turn_time = 0; // This will help determine if a task has reached the time quantum while in cpu.
	}

    // The scheduling policy goes until both the task array and ready queue are empty.
	while((empty_task = task_empty(task_array, count)) != 1 || (empty_ready = ready_empty(ready_queue, ready_index)) != 1) {
		// For each task in the task array, determine if it is ready to be be placed in the ready queue.
        int j;
		for(j = 0; j < count; j++) {
			if(task_array[j].arrival_time <= clock && task_array[j].ready == 0) {
				task_array[j].ready = 1; // Mark that it is in the ready queue.
				task_array[j].remaining_time = task_array[j].burst_time;
				ready_queue[ready_index] = task_array[j]; // Put the task in the ready queue.		
				ready_index = ready_index + 1; // Increment the amount of values in the ready queue.		
			}
		}
		
        // Check that the ready queue is not empty before trying to run a task.
		if((empty_ready = ready_empty(ready_queue, ready_index)) != 1) {
            // Go through the ready queue and find the first task that is not done.
			int k;
			int index; // Which element in queue is picked.
			for(k = 0; k < ready_index; k++) {
				if(ready_queue[k].done == 0) {
					task = ready_queue[k];
					index = k;
					break;			
				}
			}
			
            // Set the start time for tasks that have not had any cpu time yet.
			if(task.remaining_time == task.burst_time) {
				task.start_time = clock;
			}
			
			task.remaining_time--; // Decrement the remaining time.
			task.current_turn_time++; // Increment the amount of time the process has spent in the cpu this turn.
			printf("<time %u> process %u is running\n", clock, task.pid);
			clock = clock + 1; // Increment the clock.
			ready_queue[index] = task; // Update the ready queue.

			// Check to see if the process has finished its task.
			if(task.remaining_time == 0) {
				printf("<time %u> process %u is finished...\n", clock, task.pid);
				task.end_time = clock; // Set the finish time.
				ready_queue[index] = task; // Update the ready queue.
				ready_queue[index].done = 1; // "Remove" the task from the ready queue.
				finished_tasks[finished_index] = task; // Add the task to the finished tasks.
				finished_index = finished_index + 1; // Increment the amount of finished tasks.		
			// Otherwise if the process has reached the time quantum for the cpu, shift it to the end of the ready queue.		
			} else if(task.current_turn_time == time_quantum) {
				task.current_turn_time = 0; // Reset its turn time.
				ready_queue[index] = task; // Update the ready queue. 
            	int i;
            	// Check that there are at least two elements in the ready queue.
            	if(ready_index > 1) {
					// Shift until the input task is at the end of the array.
					while(ready_queue[ready_index - 1].pid != task.pid) {
						// Set temp to be the first value in the queue.
						task_t temp = ready_queue[0];
						// Shift all the values to the left.
						for(i = 0; i < ready_index - 1; i++) {
							ready_queue[i] = ready_queue[i + 1];
						}
						// Replace the last value in the ready queue with the temp value.
						ready_queue[ready_index - 1] = temp;
					}
            	}
			}
		
		} else { // If the ready queue is empty, no task is running.
			printf("<time %u> no process is running\n", clock);
			clock = clock + 1; // Increment clock.
		}
		
	}

    printf("<time %u> all processes finished ......\n", clock);

}


/*
 * Method definition for shortest remaining time first scheduling policy.
 * Takes the task array, its length, and an empty array as parameters.
 */
void srtf(task_t task_array[], u_int count, task_t finished_tasks[]) {
	// Initialize some variables to help with the policy.
	u_int clock = 0;
	u_int ready_index = 0;
	u_int finished_index = 0;
	int empty_task = 0;
	int empty_ready = 0;
	task_t task;
	task_t ready_queue[count];
	
    // Initialize the variables that describe the state of a task.
	int i;
	for(i = 0; i < count; i++) {
		task_array[i].ready = 0;
		task_array[i].done = 0;
	}

    // The scheduling policy goes until both the task array and ready queue are empty.
	while((empty_task = task_empty(task_array, count)) != 1 || (empty_ready = ready_empty(ready_queue, ready_index)) != 1) {
		// For each task in the task array, determine if it is ready to be be placed in the ready queue.
       	int j;
		for(j = 0; j < count; j++) {
			if(task_array[j].arrival_time <= clock && task_array[j].ready == 0) {
				task_array[j].ready = 1; // Mark that it is in the ready queue.
				task_array[j].remaining_time = task_array[j].burst_time;
				ready_queue[ready_index] = task_array[j]; // Put the task in the ready queue.		
				ready_index = ready_index + 1; // Increment the amount of values in the ready queue.		
			}
		}
		
        // Check that the ready queue is not empty before trying to run a task.
		if((empty_ready = ready_empty(ready_queue, ready_index)) == 0) {
			u_int shortest_time_remaining = 1000; // Set the shortest time to a large value to begin with.
            // Check each element in the ready queue to see if it has the shortest remaining time.
			int k;
			u_int index; // Which element in queue is picked.
			for(k = 0; k < ready_index; k++) {
				if(ready_queue[k].done == 0) {
					if(ready_queue[k].remaining_time < shortest_time_remaining) {
						task = ready_queue[k];
						shortest_time_remaining = task.remaining_time;
						index = k;
					}	
				}
			}

            // Set the start time for tasks that have not had any cpu time yet.
			if(task.remaining_time == task.burst_time) {
				task.start_time = clock;
			}
			
			task.remaining_time--; // Decrement the task's remaining time.
			printf("<time %u> process %u is running\n", clock, task.pid);
           	clock = clock + 1; // Increment the clock.
			ready_queue[index] = task; // Update ready queue with task

            // Check if the task is done running.
			if(task.remaining_time == 0) {
				printf("<time %u> process %u is finished...\n", clock, task.pid);
				task.end_time = clock; // Set the finish time.
				ready_queue[index] = task; // Update ready queue with task
				ready_queue[index].done = 1; // "Remove" from ready queue
				finished_tasks[finished_index] = ready_queue[index]; // Add the task to the finished tasks.
				finished_index = finished_index + 1; // Increment the amount of finished tasks.				
			}

		} else { // If the ready queue is empty, no task is running.
			printf("<time %u> no process is running\n", clock);
            clock = clock + 1; // Increment the clock.
		}

	}

    printf("<time %u> all processes finished ......\n", clock);
	
}

/* HELPER METHOD DEFINITIONS */

/* 
 * Takes in the task array and its length as parameters.
 * Returns a 1 if the task array is empty, 0 otherwise.
 */
int task_empty(task_t task_array[], u_int count) {
	int i;
	int amount_ready = 0;
    // Goes through every element in the task array.
	for(i = 0; i < count; i++) {
        // For each element in the array check if it has been put in the ready queue.
		if(task_array[i].ready == 1) {
            // Increment the count on how many tasks have been placed in the ready queue.
			amount_ready++;
		}
	}
    // If all the tasks have been put in the ready queue, then return 1.
	if(amount_ready == count) {
		return 1;
	} else {
    // Otherwise there are still tasks waiting to be put in the ready queue, return 0.
		return 0;
	}
}

/* 
 * Takes in the ready queue and its length as parameters.
 * Returns a 1 if the ready queue is empty, 0 otherwise.
 */
int ready_empty(task_t ready_queue[], u_int ready_index) {
	int i;
	int amount_done = 0;
    // Goes through every element in the ready queue.
	for(i = 0; i < ready_index; i++) {
        // For each element in the queue check if it has completed its task.
		if(ready_queue[i].done == 1) {
            // Increment the count on how many tasks are done.
			amount_done++;
		}
	}
    // If all the tasks in the ready queue are done, then return 1.
	if(amount_done == ready_index) {
		return 1;
	} else { // Otherwise there are still tasks waiting to complete their tasks, return 0.
		return 0;
	}
}
