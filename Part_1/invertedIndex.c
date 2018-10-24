#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BSTree.h"
#include "readData.h"
#include "invertedIndex.h"
#include "posix.h"

void invIndexBuilder (List l, BSTree t) {

    struct node *curr = l->head;
    while (curr != NULL) {

        char * filename = malloc(strlen(curr->url) + strlen(".txt") + 1);
		strcpy(filename, curr->url);
        strcat(filename, ".txt");
        FILE *fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("Error could not open");
            fclose(fp);
            free(filename);
			return;
        }
        //come back later and FIX
        char str[100];
        int s2flag = 0;

        while(fscanf(fp, "%s", str) != EOF) {

            if (strstr(str, "#start") || strstr(str, "#end")) {
                s2flag++;
            }

            if (strstr(str, "Section-2")) {
                s2flag++;
				continue;
            }

            if (s2flag == 4) {
                char *str_to_insert = normalise(str);
                t = BSTInsert(t,curr->url, str_to_insert);
            }

        }



        fclose(fp);
        free(filename);
        curr = curr->next;


    }


	FILE* fp = fopen("invertedIndex.txt", "w");
	if (fp == NULL) {

		printf("you suck");
		exit(-1);

	}
	writeBSTree(t, fp);
	fclose(fp);
}
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
