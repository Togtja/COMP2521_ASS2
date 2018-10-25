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


List_SFR newList();

void printList(List_SFR L);

void printOnlyUrls(List_SFR L);
void fprintOnlyUrls(List_SFR L, FILE *fp);

void insertList(char str[], List_SFR L);

void listOfUrls(char file[], List_SFR l);
//Copies lists
List_SFR copy(List_SFR l);
//deltes list
void deleteList(List_SFR l);
//merges two list and frees the second agrument/list
List_SFR mergeList(List_SFR l1, List_SFR l2);
#endif
