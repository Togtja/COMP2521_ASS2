// Queue.h ... implementation of Queue ADT
// assumes that Item is an assignable type
// (e.g. int, pointer) defined in Queue.h

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "queue.h"

typedef struct QueueNode {
	char * value;
	struct QueueNode *next;
} QueueNode;

typedef struct QueueRep {
	QueueNode *head;  // ptr to first node
	QueueNode *tail;  // ptr to last node
} QueueRep;

// create new empty Queue
Queue newQueue()
{
	Queue q;
	q = malloc(sizeof(QueueRep));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	return q;
}

// free memory used by Queue
void dropQueue(Queue Q)
{
	QueueNode *curr, *next;
	assert(Q != NULL);
	// free list nodes
	curr = Q->head;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	// free queue rep
	free(Q);
}

// display as 3 > 5 > 4 > ...
void showQueue(Queue Q)
{
	QueueNode *curr;
	assert(Q != NULL);
	// free list nodes
	curr = Q->head;
	while (curr != NULL) {
		printf("%s\n",(curr->value));
		if (curr->next != NULL)
			printf(" > ");
		curr = curr->next;
	}
	// free queue rep
	free(Q);
}

// add item at end of Queue
void QueueJoin(Queue Q, char* it)
{
	assert(Q != NULL);
	QueueNode *new = malloc(sizeof(QueueNode));
	assert(new != NULL);
	new->value = it;
	new->next = NULL;
	if (Q->head == NULL)
		Q->head = new;
	if (Q->tail != NULL)
		Q->tail->next = new;
	Q->tail = new;
}

// remove item from front of Queue
char* QueueLeave(Queue Q)
{
	assert(Q != NULL);
	assert(Q->head != NULL);
	char * it = Q->head->value;
	QueueNode *old = Q->head;
	Q->head = old->next;
	if (Q->head == NULL) Q->tail = NULL;
	free(old);
	return it;
}

// check for no items
int QueueIsEmpty(Queue Q)
{
	return (Q->head == NULL);
}
