#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
void invIndexBuilder(List l, BSTree t);
//changes the pointer to lower
void stringToLower(char* str);
//removes ',' '.' ':' '?' from string
void removeNonLetters(char* str);
//returns the normal of the string
char* normalise(const char * str);
#endif