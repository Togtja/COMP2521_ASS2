#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"
#include "pagerank.h"

int main() {


    List l = newList();
    listOfUrls("collection", l);
    printList(l);
    printf("%d\n", l->size);

    Graph urlConnections = newGraph(l->size);
    graphBuilder(l, urlConnections);
    showGraph(urlConnections, 1);
    //printf("Start showing showQueue()\n");
    //showQueue(q);
    //printf("Start showing own function\n");
    //while (!QueueIsEmpty(q)) {
    //	char* str = QueueLeave(q);
    //	printf("%s\n", str);
    //}

    return 0;

}
