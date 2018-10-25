#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "readData_Tfldf.h"
#include "normaliser.h"
#include "posix.h"


void stringToLower_Part2(char *str) {
	char* s;
	for (s = str; *s; ++s) *s = *s >= 'A'&&*s <= 'Z' ? *s | 0x60 : *s;
}
//Author Fabio Cabral
//https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
void removeNonLetters_Part2(char *str) {
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
char* normalise_Part2(const char * str) {
	char* p = nStrdup(str);
	stringToLower_Part2(p);
	removeNonLetters_Part2(p);
	return p;
}
