// BSTree.c ... implementation of binary search tree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "readData.h"

typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	char * key;
    List urlList;
	BSTLink left, right;
} BSTNode;

// make a new node containing a value
static
BSTLink newBSTNode(char *keyword)
{
	BSTLink new = malloc(sizeof(BSTNode));
	assert(new != NULL);
	new->key = strdup(keyword);
	new->left = new->right = NULL;
    new->urlList = newList();
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

void BSTInsert(BSTree t, char *url, char* keyword){

    if (t == NULL) {
        t = newBSTNode(keyword);
        insertList(url, t->urlList);
    }

}

// display a BSTree
void showBSTree(BSTree t)
{
	if (t == NULL)
        return;

    showBSTree(t->left);

    printf("%s  ", t->key);
    printOnlyUrls(t->urlList);

    showBSTree(t->right);

}

void writeBSTree(BSTree t, FILE *fp)
{
	if (t == NULL)
        return;

    writeBSTree(t->left, fp);

    fprintf(fp, "%s  ", t->key);
    printOnlyUrls(t->urlList);

    writeBSTree(t->right, fp);

}
