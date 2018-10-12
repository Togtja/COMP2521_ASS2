#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"

Queue listOfUrls(char file[]){
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

    Queue q = newQueue();
    while(fscanf(fp, "%s", str) != EOF) {
        printf("%s\n", str);
        QueueJoin(q, str);
    }

    fclose(fp);
    free(filename);
    return q;
	//Make a list (Queue/Stack) of the URLS
	//Return the URL list
}

int main() {

    
    Queue q = listOfUrls("collection");
    printf("Start showing showQueue()\n");
    showQueue(q);
    printf("Start showing own function\n");
    while (!QueueIsEmpty(q)) {
    	char* str = QueueLeave(q);
    	printf("%s\n", str);
    }

    return 0;

}

//Graph getGraph(List urls) {
	//Create an empty list
	//Get first element of the list
	//While list is not empty
		//Read the url
		//Update graph by adding node and outgoinf links
	//End while
//}
//List getInvertedList(List urls) {
	//Don't understand what this one is suppsed to do
//}
