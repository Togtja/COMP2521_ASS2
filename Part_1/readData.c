#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"

void listOfUrls(char file[]){
	//Find the file
    char * filename = malloc(strlen(file) + strlen(".txt") + 1);
    strcpy(filename, file);
    strcat(filename,".txt");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: file collection.txt can not open\n");
        return;
    }

    char *str;


    while(fscanf(fp, "%s", str) != EOF) {
        printf("%s\n", str);
    }

    fclose(fp);
    free(filename);

	//Make a list (Queue/Stack) of the URLS
	//Return the URL list
}

int main() {

    listOfUrls("collection");
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
