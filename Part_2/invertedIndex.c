#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData.h"
#include "invertedIndex.h"
#include "posix.h"

void stringToLower(char *str) {
	char* s;
	for (s = str; *s; ++s) *s = *s >= 'A'&&*s <= 'Z' ? *s | 0x60 : *s;
}
//Author Fabio Cabral
//https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
void removeNonLetters(char *str) {
	char *src, *dst;
	for (src = dst = str; *src; src++) {
		*dst = *src;
		if (*dst != '.' &&
			*dst != ',' &&
			*dst != ';' &&
			*dst != '?') dst++;
	}
	*dst = '\0';
}
char* normalise(const char * str) {
	char* p = nStrdup(str);
	stringToLower(p);
	removeNonLetters(p);
	return p;
}
List fileToList(char* find) {

	FILE* fp = fopen("invertedIndex.txt", "r");
	if (fp == NULL) {
		printf("Could not find invertedIndex.txt");
		exit(-1);
	}
	char str[1000];
	List list = newList();
	//get the first line
	while (fgets(str, 1000, fp) != NULL) {
		char* word = strstr(str, find);
		//if the word we are looking for isn't in the line,
		if (word == NULL) {
			//go to the next line
			continue;
		}
		//We have found the word
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
		}
		fclose(fp);
		return list;
	}
	printf("Could not find the word");
	return NULL;
}
int numOfWordsinFile() {
	int i = 0;
	FILE* fp = fopen("invertedIndex.txt", "r");
	char str[1000];
	//get the first line
	while (fgets(str, 1000, fp) != NULL) {
		i++;
	}
	return i;
}