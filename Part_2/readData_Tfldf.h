#ifndef READDATA_TFLDF_H
#define READDATA_TFLDF_H

#include "posix.h"

struct node_Tfldf {
    char * url;
    struct node_Tfldf *next;
    int pos;
	float TfIdfValue;
	int rankVal;
};

struct List_Tfldf {

    struct node_Tfldf *head;
    struct node_Tfldf *curr;
    int size;

};

typedef struct List_Tfldf *List_Tfldf;


List_Tfldf newList();

void printList(List_Tfldf L);

void printOnlyUrls(List_Tfldf L);
void fprintOnlyUrls(List_Tfldf L, FILE *fp);

void insertList(char str[], List_Tfldf L);

void listOfUrls(char file[], List_Tfldf l);
//Copies lists
List_Tfldf copy(List_Tfldf l);
//deltes list
void deleteList(List_Tfldf l);;
//Bubble sort the Rank Values
void BubbleSortListRV(List_Tfldf ret);
//Bubble sort the TFIDF values
void BubbleSortListTFIDF(List_Tfldf ret);
//merges two list and frees the second agrument/list
List_Tfldf mergeList(List_Tfldf l1, List_Tfldf l2);
List_Tfldf fileToList(char* find);
#endif
