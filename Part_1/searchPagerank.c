#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pagerank.h"

int main(int argc, char* argv[]) {



	//List* list = malloc(c * sizeof(List));
	List mainL = fileToList(argv[1]);
	int i;
	for (i = 2; i < argc; i++) {
		List list = fileToList(argv[i]);
		mergeList(mainL, list);//merge free second argument
	}

	//DELETE LIST OF LIST
	printf("\n\nMERGED: \n");
	printList(mainL);

	printf("\n\nRPList\n\n");
	PRList(mainL);
	printf("\n\nSortListPR\n\n");
	BubbleSortListPR(mainL);
	printf("\n\nSortListRV\n\n");
	BubbleSortListRV(mainL);
	printList(mainL);
	deleteList(mainL);
	char k = getchar();
	putchar(k);
	return 0;
}
