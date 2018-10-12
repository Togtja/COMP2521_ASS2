// Queue.h ... interface to Queue-of-BSTree-nodes ADT

#ifndef QUEUE_H
#define QUEUE_H


typedef struct QueueRep *Queue;

Queue newQueue(); // create new empty queue
void dropQueue(Queue); // free memory used by queue
void showQueue(Queue); // display as 3 > 5 > 4 > ...
void QueueJoin(Queue, char *); // add item on queue
char* QueueLeave(Queue); // remove item from queue
int QueueIsEmpty(Queue); // check for no items

#endif
