#include <stdio.h>
#include<stdlib.h>
#include <string.h>

//cause we cant use POSIX
//:(((((((((((((((
char * nStrdup(const char *s) {
    char *c = malloc(strlen(s) + 1);
    if (c == NULL)
        return NULL;
    strcpy(c, s);
    return c;

}
