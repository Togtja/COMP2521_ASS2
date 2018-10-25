#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "BSTree.h"
#include "readData.h"
#include "invertedIndex.h"
#include "posix.h"

int main() {
    //read in urls
    List url_list = newList();
    listOfUrls("collection", url_list);

    //create BSTree and dump results into .txt file
    BSTree BST = newBSTree();
	invIndexBuilder(url_list, BST); //BSTree freed inside here
	dropBSTree(BST);

    deleteList(url_list);

    printf("Completed!\n");
    return EXIT_SUCCESS;

}

