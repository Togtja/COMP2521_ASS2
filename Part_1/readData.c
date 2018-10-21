#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"



struct node {
    char * url;
    struct node *next;
};

struct List {

    struct node *head;
    struct node *curr;
    int size;

};

typedef struct List *List;

void graphBuilder(List urls, Graph g);

List newList() {
    List list = malloc(sizeof(struct List));
    list->head = NULL;
    list->curr = NULL;
    list->size = 0;
    return list;
}

void printList(List L) {

    struct node *ptr = L->head;
    while (ptr != NULL) {
        printf("%s\n", ptr->url);
        ptr = ptr->next;
    }
}

void insert(char str[], List L) {
    struct node *link = malloc(sizeof(struct node));
    link->url = malloc(strlen(str) * sizeof(char) + 1);
    strcpy(link->url, str);
    link->next = NULL;
    if (L->head == NULL) {
        L->head = link;
        L->curr = L->head;
    } else {
        L->curr->next = link;
        L->curr = L->curr->next;
    }

    L->size++;
}

void listOfUrls(char file[], List l){
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
        insert(str,l);
      //  QueueJoin(q, str);
    }

    fclose(fp);
    free(filename);
    //return q;
	//Make a list (Queue/Stack) of the URLS
	//Return the URL list
}

int main() {


    List l = newList();
    listOfUrls("collection", l);
    printList(l);
    printf("%d\n", l->size);

    Graph urlConnections = newGraph(l->size);
    graphBuilder(l, urlConnections);
    showGraph(urlConnections, 1);
    //printf("Start showing showQueue()\n");
    //showQueue(q);
    //printf("Start showing own function\n");
    //while (!QueueIsEmpty(q)) {
    //	char* str = QueueLeave(q);
    //	printf("%s\n", str);
    //}

    return 0;

}

void graphBuilder(List urls, Graph g) {
	//Create an empty list
	//Get first element of the list
	//While list is not empt
    struct node *cur = urls->head;
    addVertex(cur->url, g->vertex, g->nV);

    while (cur != NULL && nVertices(g) <= urls->size) {

        char *url_name = malloc(strlen(cur->url) + strlen(".txt") + 1);
        strcpy(url_name, cur->url);
        strcat(url_name, ".txt");

        printf("opening %s\n", url_name);

        FILE *fp = fopen(url_name, "r");

        if (fp == NULL) {
            printf("h");
        }

        char str[100];

        while (fscanf(fp, "%s", str) != EOF) {

            if (!strstr(str, "url")) {
                continue;
            }

            if(!isConnected(g, cur->url, str)) {
                addEdge(g, cur->url, str);
                printf("%s -> %s\n", cur->url, str);
            }

        }

        fclose(fp);
        free(url_name);

        cur = cur->next;

    }
		//Read the url
		//Update graph by adding node and outgoinf links
	//End while
}
//List getInvertedList(List urls) {
	//Don't understand what this one is suppsed to do
//}
