#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData_Tfldf.h"
#include "normaliser.h"
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
