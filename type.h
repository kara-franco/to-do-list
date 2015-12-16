/* Task structure can store the task description and priority. Tasks build dynamic array. */

#ifndef __TYPE_H
#define __TYPE_H

#define TASK_DESC_SIZE 128

struct Task {
	char description[TASK_DESC_SIZE];  	/* description of the task */
	int priority;			  			/* task priority */
};

typedef struct Task Task;

#endif
