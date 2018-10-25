#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pagerank.h"



int main(int argc, char* argv[]) {

	//List* list = malloc(c * sizeof(List));
	List manL = fileToList(argv[1]);
	int i;
	for (i = 2; i < argc; i++) {
		char* temp = normalise(argv[i]);
		List list = fileToList(temp);
		mergeList(manL, list);//merge free second argument
		free(temp);
	}
	PRList(manL);
	BubbleSortListPR(manL);
	BubbleSortListRV(manL);
	printList(manL);
	deleteList(manL);
	return 0;
}
