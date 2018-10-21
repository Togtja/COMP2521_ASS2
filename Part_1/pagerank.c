#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"
#include "pagerank.h"

int main(int argc, char *argv[]) {


    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    double maxIterations = atof(argv[3]);

    printf("%lf, %lf, %lf\n", d, diffPR, maxIterations);

    List l = newList();
    listOfUrls("collection", l);
    printList(l);
    printf("%d\n", l->size);

    Graph urlConnections = newGraph(l->size);
    graphBuilder(l, urlConnections);
    showGraph(urlConnections, 1);

    //build a list of the page ranks of each url
    //and set them all to 1/N, N being num of urls

    //int i = 0
    //diff = diffPR;
    //while (i < maxIterations and diff >= diffPR ) {
    //the pagerank of each url(pi) at i + 1 is:
    //1-d/(num of urls) + d * sum (for all urls that connect to pi (pj)) of
    //(pagerank of pj at i) * ((number of urls connecting to pi)/(number of urls connecting to
    //every url pj connects to)) * ((number of urls pi connects to)/(number of urls that each
    //url connecting to pj connects to))
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //

    return 0;

}
