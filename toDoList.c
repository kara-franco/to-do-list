/* toDoList.c: An implementation of a To Do List */

/**************************************************************
 * Author: Kara Franco			           Assignment #5      *
 * lallyk@oregonstate.edu		              CS 261-400      *
 * Due Date: August 3, 2015                                   *
 * Program Description: This program uses the dynamic array   *
 * implementation of the heap abstract data type to create,   *
 * manage and delete items on a to do list.                   *
 **************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "toDoList.h"


/*  Create a task from the description and the priority

param:  priority    priority of the task
param:  desc    	pointer to the description string
pre:    none
post:   none
ret: 	a task with description and priority
*/
Task* createTask(int priority, char *desc)
{
	// create space for new task
	Task* newTask = malloc(sizeof(Task));
	// copy description into the task structure
	strcpy(newTask->description, desc);
	// set priority to newTask
	newTask->priority = priority;

	return newTask;
}

/*  Save the list to a file

param:  heap    pointer to the list
param:  filePtr	pointer to the file to which the list is saved
pre:    The list is not empty
post:   The list is saved to the file in tab-delimited format.
Each line in the file stores a task, starting with the
task priority, followed by a tab character (\t), and
the task description.

The tasks are not necessarily stored in the file in
priority order.

*/
void saveList(DynArr *heap, FILE *filePtr)
{
	int i;
	Task* task;
	assert(sizeDynArr(heap) > 0);
	for (i = 0; i < sizeDynArr(heap); i++)
	{
		task = getDynArr(heap, i);
		fprintf(filePtr, "%d\t%s\n", task->priority, task->description);
	}
}

/*  Load the list from a file

param:  heap    pointer to the list
param:  filePtr	pointer to the file
pre:    none
post:   The tasks are retrieved from the file and are added to the list.
Refer to the saveList() function for the format of tasks in the file
*/
void loadList(DynArr *heap, FILE *filePtr)
{
	Task* task;
	char line[100];  /* Assume lines < 100 */
	char desc[TASK_DESC_SIZE], *nlptr;
	int priority;

	/* Read the priority first, then the description.
	 * fgets() is used to read string with spaces
	 */
#ifdef NOTDEF
	while (fscanf(filePtr, "%d\t", &priority) != EOF)
	{
		/* fgets() stops reading at \n character */
		fgets(desc, sizeof(desc), filePtr);
		/* remove trailing newline character */
		nlptr = strchr(desc, '\n');
		if (nlptr)
			*nlptr = '\0';

		task = createTask(priority, desc);
		addHeap(heap, task);
	}
#endif

	while (fgets(line, sizeof(line), filePtr) != 0)
	{
		sscanf(line, "%d\t%[^\n]", &priority, desc);
		task = createTask(priority, desc);
		addHeap(heap, task);
	}

}

/*  Print the list

param:  heap    pointer to the list
pre:    the list is not empty
post:   The tasks from the list are printed out in priority order.
The tasks are not removed from the list.
*/
void printList(DynArr *heap)
{
	// create a temporary array to hold elements while printing
	DynArr *temporary = createDynArr(sizeDynArr(heap));
	Task* task;
	assert(sizeDynArr(heap) > 0);
	// copy the array named heap to temp array
	copyDynArr(heap, temporary);
	// print the task: first get the task, print the task, remove the task
	printf("\n");
	while (sizeDynArr(temporary) > 0){
		task = getMinHeap(temporary);
		printf("%s \n", task->description);
		removeMinHeap(temporary);
	}
	printf("\n");
	// free the temporary list
	deleteDynArr(temporary);

}

/*  Delete the list

param:  heap    pointer to the list
post:   The tasks from the list are removed and their occupied memories are freed

*/
void deleteList(DynArr *heap)
{

	Task* task;
	while (sizeDynArr(heap) > 0)
	{
		/* get the task */
		task = getMinHeap(heap);
		/* remove the task */
		removeMinHeap(heap);
		/* free the task */
		free(task);
	}
	/* free the heap */
	deleteDynArr(heap);
}

/*  Compare two tasks by priority

param:  left    first task
param:  right 	second task
pre:    none
post:   none
ret: 	-1 if priority of left < priority of right
1 if priority of left > priority of right
0 if priority of left = priority of right
*/

int compare(TYPE left, TYPE right)
{

	// cast left and right to the corresponding pointer type
	Task* leftCast = (Task*)left;
	Task* rightCast = (Task*)right;

	// compare the tasks priority
	if (leftCast->priority < rightCast->priority){
		// if less thatn return -1
		return -1;
	}
	else if (leftCast->priority > rightCast->priority){
		// if greater than return 1
		return 1;
	}
	else {
		return 0;
	}
}

/*Define this function, type casting the value of void * to the desired type*/
void print_type(TYPE curval)
{

	Task* data1;
	data1 = (Task*)curval;
	printf("%d\t%s\n", data1->priority, data1->description);
}

