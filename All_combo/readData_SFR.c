#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData_SFR.h"
#include "posix.h"

List_SFR newList_SFR() {
    List_SFR list = malloc(sizeof(struct List_SFR));
    list->head = NULL;
    list->curr = NULL;
    list->size = 0;
    return list;
}

void printList_SFR(List_SFR l) {

    l->curr = l->head;
    while (l->curr != NULL) {
		printf("%s", l->curr->url);
		l->curr = l->curr->next;
    }
}

void printOnlyUrls_SFR(List_SFR L) {

    struct node_SFR *ptr = L->head;
    while (ptr != NULL) {
        printf("%s ", ptr->url);
        ptr = ptr->next;
    }
    printf("\n");

}

void fprintOnlyUrls_SFR(List_SFR L, FILE *fp) {

    struct node_SFR *ptr = L->head;
    while (ptr != NULL) {
        fprintf(fp, "%s ", ptr->url);
        ptr = ptr->next;
    }
    fprintf(fp, "\n");

}



void insertList_SFR(char str[], List_SFR L) {
    struct node_SFR *link = malloc(sizeof(struct node_SFR));
    link->url = malloc(strlen(str) * sizeof(char) + 1);
    strcpy(link->url, str);
    link->next = NULL;
    if (L->head == NULL) {
        L->head = link;
        L->curr = L->head;
        L->head->pos = 0;
    } else {
		L->curr = L->head;
		while (L->curr->next != NULL) {
			L->curr = L->curr->next;
		}
        L->curr->next = link;
        L->curr = L->curr->next;
        L->curr->pos = L->size;
    }

    L->size++;
}

void listOfUrls_SFR(char file[], List_SFR l){
	//Find the file
    char * filename = malloc(strlen(file) + strlen(".txt") + 1);
    strcpy(filename, file);
    strcat(filename,".txt");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: file collection.txt can not open\n");
        //return 0;
    }

    char str[10];

    //Queue q = newQueue();
    while(fscanf(fp, "%s", str) != EOF) {
        //printf("hey %s\n", str);
        insertList_SFR(str,l);
      //  QueueJoin(q, str);
    }

    fclose(fp);
    free(filename);
    //return q;
	//Make a list (Queue/Stack) of the URLS
	//Return the URL list
}


//List getInvertedList(List urls) {
	//Don't understand what this one is suppsed to do
//}
void add_SFR(List_SFR l,struct node_SFR * newN) {
	if (l->head == NULL) {
		l->head = newN;
	}
	else {
		l->curr = l->head;
		while (l->curr->next != NULL) {
			l->curr = l->curr->next;
		}
		l->curr->next = newN;
	}
	l->size++;
}
List_SFR copy_SFR(List_SFR l) {
	List_SFR cpy = newList_SFR();
	l->curr = l->head;
	while (l->curr != NULL) {
		struct node_SFR *newN = malloc(sizeof(struct node_SFR));
		newN->next = NULL;//Will set to correct next in add
		newN->pos = l->curr->pos;
		newN->url = nStrdup(l->curr->url);
		l->curr = l->curr->next;
		add_SFR(cpy, newN);
	}
	return cpy;
}

void deleteList_SFR(List_SFR l) {
	if (l == NULL) {
		return;
	}
	l->curr = l->head; 
	while (l->curr != NULL) {
		struct node_SFR* remv = l->curr;
		l->curr = l->curr->next;
		free(remv->url);
		free(remv);
	}
	free(l);
}
List_SFR mergeList_SFR(List_SFR l1, List_SFR l2) {
	l2->curr = l2->head;
	while (l2->curr != NULL) {
		l1->curr = l1->head;
		int inside = 0;
		while (l1->curr != NULL) {
			if (strcmp(l1->curr->url, l2->curr->url) == 0) {
				inside = 1;
				break;
			}
			l1->curr = l1->curr->next;
		}
		if (inside == 0) {
			insertList_SFR(l2->curr->url, l1);
		}
		l2->curr = l2->curr->next;
	}
	deleteList_SFR(l2);
	return l1;
}
