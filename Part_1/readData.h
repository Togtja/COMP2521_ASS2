#ifndef READDATA_H
#define READDATA_H

#include "graph.h"

struct node {
    char * url;
    struct node *next;
    int pos;
    int in;
    int out;
	float val;
};

struct List {

    struct node *head;
    struct node *curr;
    int size;
	Graph graph;

};

typedef struct List *List;

void graphBuilder(List urls, Graph g);

List newList();

void printList(List L);

void insertList(char str[], List L);

void listOfUrls(char file[], List l);
//Initialized the pagerank list
void initPR(List l);
//Copies lists
List copy(List l);
//TODO Make a delete

#endif
