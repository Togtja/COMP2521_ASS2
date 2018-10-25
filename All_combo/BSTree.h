// BSTree.h ... interface to binary search tree ADT
#ifndef BSTREE_H
#define BSTREE_H
#include <stdio.h>
#include "readData.h"
#include "posix.h"

typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree();

void dropBSTree(BSTree t);

BSTree BSTInsert(BSTree t, char *url, char* keyword);

void showBSTree(BSTree t);

void writeBSTree(BSTree t, FILE *fp);

//List findInBSTree(BSTree t, char* str);
#endif
