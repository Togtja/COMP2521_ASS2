#ifndef READDATA_SFR_H
#define READDATA_SFR_H

#include "posix.h"

struct node_SFR {
    char * url;
    struct node_SFR *next;
    int pos;
};

struct List_SFR {

    struct node_SFR *head;
    struct node_SFR *curr;
    int size;

};

typedef struct List_SFR *List_SFR;


List_SFR newList_SFR();

void printList_SFR(List_SFR L);

void printOnlyUrls_SFR(List_SFR L);
void fprintOnlyUrls_SFR(List_SFR L, FILE *fp);

void insertList_SFR(char str[], List_SFR L);

void listOfUrls_SFR(char file[], List_SFR l);
//Copies lists
List_SFR copy_SFR(List_SFR l);
//deltes list
void deleteList_SFR(List_SFR l);
//merges two list and frees the second agrument/list
List_SFR mergeList_SFR(List_SFR l1, List_SFR l2);
#endif
