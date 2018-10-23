#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BSTree.h"
#include "readData.h"
#include "invertedIndex.h"

void invIndexBuilder (List l, BSTree t) {

    l->curr = l->head;
    while (l->curr != NULL) {

        char * filename = malloc(strlen(l->curr->url) + strlen(".txt") + 1);
        strcat(filename, ".txt");
        FILE *fp = fopen(filename, "r");

        if (fp == NULL) {
            printf("Error could not open");
            fclose(fp);
            free(filename);
            exit(-1);
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
            }

            if (s2flag == 4) {
                BSTInsert(t,l->curr->url, str);
            }

        }

        fclose(fp);
        free(filename);
        l->curr = l->curr->next;


    }

}
