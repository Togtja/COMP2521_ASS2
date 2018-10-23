// BSTree.h ... interface to binary search tree ADT
#ifndef BSTREE_H
#define BSTREE_H
#include <stdio.h>

typedef struct BSTNode *BSTree;

// create an empty BSTree
BSTree newBSTree();

void dropBSTree(BSTree t);

void BSTInsert(BSTree t, char *url, char* keyword);

void showBSTree(BSTree t);

void writeBSTree(BSTree t, FILE *fp);
#endif
