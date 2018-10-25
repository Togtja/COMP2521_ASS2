#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "readData.h"
#include "invertedIndex.h"
#include "posix.h"


float TFsearchUrl(char* url, char* word);
List numOfDocumets();
int wordAppear(List l, char * word);

int main(int argc, char* argv[]) {

	List bigBoy = fileToList(argv[1]);
	if (bigBoy == NULL) {
        return 0;
    }
    int i;
	for (i = 2; i < argc; i++) {
		List list = fileToList(argv[i]);
//        printList(list);
		mergeList(bigBoy, list);
	}
	List urls = numOfDocumets();
	//float IDF = log10f((float)numDocs / (float)bigBoy->size);
	bigBoy->curr = bigBoy->head;
	while (bigBoy->curr != NULL) {

		int j;
		for ( j = 1; j < argc; j++) {
//            printf("%s\n", bigBoy->curr->url);
			//struct node * currtmp = bigBoy->curr;
			float IDF = log10f( (float)urls->size / (float)wordAppear(urls, argv[j]));
			//printf("IDF: %.7f \t bigboy %d \t size %d ", IDF, bigBoy->size, wordAppear(bigBoy, v[j]));
			//bigBoy->curr = currtmp;
			float TFvalue = TFsearchUrl(bigBoy->curr->url, argv[j]);
			bigBoy->curr->TfIdfValue += TFvalue * IDF;
		}

		bigBoy->curr = bigBoy->curr->next;
	}
	BubbleSortListTFIDF(bigBoy);
	BubbleSortListRV(bigBoy);

	printList(bigBoy);
	char q = getchar();
	putchar(q);
    deleteList(urls);
    deleteList(bigBoy);
    return EXIT_SUCCESS;
}
float TFsearchUrl(char* url, char* word) {
	int numOfWrd = 0; int numTotal = 0;
	char* filename = malloc(strlen(url) + strlen(".txt") + 1);
	strcpy(filename, url);
	strcat(filename, ".txt");
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error could not open");

		exit(-1);
	}
	//come back later and FIX
	char str[100];
	int s2flag = 0;
	while (fscanf(fp, "%s", str) != EOF) {
		char* cmp = normalise(str);
		if (strstr(str, "#start") || strstr(str, "#end")) {
			s2flag++;
		}
		if (strstr(str, "Section-2")) {
			s2flag++;
		    free(cmp);
			continue;
		}
		if (s2flag == 4) {

			if (strcmp(cmp, word) == 0) {
				numOfWrd++;
			}
			numTotal++;
		}
		free(cmp);
	}

	fclose(fp);
    free(filename);
	if (numTotal == 0) {
		return 0;
	}
	return (float)numOfWrd/(float)numTotal;
}
List numOfDocumets() {
	FILE* fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		printf("Could not find collection.txt");
		exit(-1);
	}
	List urlList = newList();
	char str[100];
	while (fscanf(fp, "%s", str) != EOF) {
		insertList(str, urlList);
	}
	return urlList;
}
int wordAppear(List l, char * word) {
	l->curr = l->head; int i = 0;
	while (l->curr != NULL) {
		if (TFsearchUrl(l->curr->url, word) != 0) {
			i++;
		}
		l->curr = l->curr->next;
	}
	return i;
}
