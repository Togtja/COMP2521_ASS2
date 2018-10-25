#ifndef READDATA_H
#define READDATA_H

#include "graph.h"
#include "posix.h"

struct node {
    char * url;
    struct node *next;
    int pos;
    int in;
    int out;
	float val;
	int rankVal;
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

void printOnlyUrls(List L);
void fprintOnlyUrls(List L, FILE *fp);

void insertList(char str[], List L);

void listOfUrls(char file[], List l);
//Initialized the pagerank list
void initPR(List l);
//Copies lists
List copy(List l);
//deltes list
void deleteList(List l);
//Bubblesort the PR values
void BubbleSortListPR(List ret);
//Bubble sort the Rank Values
void BubbleSortListRV(List ret);
//sort the list by strcmp the urls
//used for outputting urls in
//Part 2
void BubbleSortListSC(List ret);
//prints a list to a file
void printListToFile(List l, char* fileName);
//merges two list and frees the second agrument/list
List mergeList(List l1, List l2);
#endif
