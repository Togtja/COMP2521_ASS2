#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
#include "BSTree.h"
#include "posix.h"
void invIndexBuilder(List l, BSTree t);
//changes the pointer to lower
void stringToLower(char* str);
//removes ',' '.' ':' '?' from string
void removeNonLetters(char* str);
//returns the normal of the string
char* normalise(const char * str);
//Set the PR values from a file
void PRList(List list);
//Makes a file into a list
List fileToList_Part2(char* find);
#endif
