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


List_Tfldf newList_Tfldf();

void printList_Tfldf(List_Tfldf L);

void printOnlyUrls_Tfldf(List_Tfldf L);
void fprintOnlyUrls_Tfldf(List_Tfldf L, FILE *fp);

void insertList__Tfldf(char str[], List_Tfldf L);

void listOfUrls__Tfldf(char file[], List_Tfldf l);
//Copies lists
List_Tfldf copy__Tfldf(List_Tfldf l);
//deltes list
void deleteList__Tfldf(List_Tfldf l);;
//Bubble sort the Rank Values
void BubbleSortListRV__Tfldf(List_Tfldf ret);
//Bubble sort the TFIDF values
void BubbleSortListTFIDF__Tfldf(List_Tfldf ret);
//merges two list and frees the second agrument/list
List_Tfldf mergeList__Tfldf(List_Tfldf l1, List_Tfldf l2);
List_Tfldf fileToList_Part2(char* find);
#endif
