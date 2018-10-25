#ifndef READDATA_TFLDF_H
#define READDATA_TFLDF_H

#include "posix.h"

struct node {
    char * url;
    struct node *next;
    int pos;
	float TfIdfValue;
	int rankVal;
};

struct List {

    struct node *head;
    struct node *curr;
    int size;

};

typedef struct List *List;


List newList();

void printList(List L);

void printOnlyUrls(List L);
void fprintOnlyUrls(List L, FILE *fp);

void insertList(char str[], List L);

void listOfUrls(char file[], List l);
//Copies lists
List copy(List l);
//deltes list
void deleteList(List l);;
//Bubble sort the Rank Values
void BubbleSortListRV(List ret);
//Bubble sort the TFIDF values
void BubbleSortListTFIDF(List ret);
//merges two list and frees the second agrument/list
List mergeList(List l1, List l2);
#endif
