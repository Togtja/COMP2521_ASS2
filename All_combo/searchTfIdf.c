#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "readData_Tfldf.h"
#include "normaliser.h"
#include "posix.h"


float TFsearchUrl(char* url, char* word);
List_Tfldf numOfDocumets();
int wordAppear(List_Tfldf l, char * word);

int main(int argc, char* argv[]) {

	List_Tfldf bigBoy = fileToList(argv[1]);
	if (bigBoy == NULL) {
        return 0;
    }
    int i;
	for (i = 2; i < argc; i++) {
		List_Tfldf list = fileToList(argv[i]);
//        printList(list);
		mergeList(bigBoy, list);
	}
	List_Tfldf urls = numOfDocumets();
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
List_Tfldf numOfDocumets() {
	FILE* fp = fopen("collection.txt", "r");
	if (fp == NULL) {
		printf("Could not find collection.txt");
		exit(-1);
	}
	List_Tfldf urlList = newList();
	char str[100];
	while (fscanf(fp, "%s", str) != EOF) {
		insertList(str, urlList);
	}
	return urlList;
}
int wordAppear(List_Tfldf l, char * word) {
	l->curr = l->head; int i = 0;
	while (l->curr != NULL) {
		if (TFsearchUrl(l->curr->url, word) != 0) {
			i++;
		}
		l->curr = l->curr->next;
	}
	return i;
}
List_Tfldf fileToList(char* find) {

	FILE* fp = fopen("invertedIndex.txt", "r");
	if (fp == NULL) {
		printf("Could not find invertedIndex.txt");
		exit(-1);
	}
	char str[1000];
	List_Tfldf list = newList();
	//get the first line
	while (fgets(str, 1000, fp) != NULL) {
		//	    printf("%s\n", str);
		char* word = strstr(str, find);
		//if the word we are looking for isn't in the line,
		if (word == NULL) {
			//go to the next line
			continue;
		}
		//We have found the word
		//assert we havent only found part of bigger word
		//eg search 'man' and found 'human'
		if (strcmp(word, str) != 0) {
			continue;
		}
		char* url1 = strstr(word, " ");
		//url1 points 2 the beginning of all the urls
		url1 = strstr(&url1[1], " "); //there is 2 space after the words
									  //url2 points at the end of the first url
		char* url2 = strstr(&url1[2], " ");
		//While not the end of the line
		while (url2 != NULL) {
			//copy the url into theUrl
			char* theUrl = malloc(strlen(url1) - strlen(url2));
			theUrl = memcpy(theUrl, &url1[1], strlen(url1) - strlen(url2) - 1);
			theUrl[strlen(url1) - strlen(url2) - 1] = '\0';
			insertList(theUrl, list);//insert the url into a new list
			url1 = url2;//url1 point to the beginning of the next url
			url2 = strstr(&url2[1], " ");//url2 point to the end of the next url
			free(theUrl);
		}
		fclose(fp);
		return list;
	}
	//printf("Could not find the word");
	return NULL;
}
