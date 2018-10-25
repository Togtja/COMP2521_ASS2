#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
#include "posix.h"
//changes the pointer to lower
void stringToLower(char* str);
//removes ',' '.' ':' '?' from string
void removeNonLetters(char* str);
//returns the normal of the string
char* normalise(const char * str);
//Makes a file into a list
List_Tfldf fileToList(char* find);
#endif
