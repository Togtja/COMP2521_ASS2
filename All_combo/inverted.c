
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include "pagerank.h"
#include <math.h>
#include "BSTree.h"
#include "invertedIndex.h"
#include "posix.h"
 
int main(int argc, char* argv[]) {
	//Make make it take in collection.txt as filename
	List url_list = newList();
	listOfUrls("collection", url_list);
	BSTree BST = newBSTree();
	invIndexBuilder(url_list, BST); //BSTree freed inside here
	dropBSTree(BST);
	
	return 0;
}