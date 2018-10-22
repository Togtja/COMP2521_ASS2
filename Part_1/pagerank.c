#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"
#include "pagerank.h"


//`void pageRanker(double d, double diffPR, double maxIterations, List urls, Graph g) {



//}



int main(int argc, char *argv[]) {


    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    double maxIterations = atof(argv[3]);

    printf("%lf, %lf, %lf\n", d, diffPR, maxIterations);

    //build list of urls
    List url_list = newList();
    listOfUrls("collection", url_list);
	initPR(url_list);
	printList(url_list);
	
    //build a list of the page ranks of each url
    //and set them all to 1/N, N being num of urls


    //build a graph representation of the connections
    //between urls
    Graph urlConnections = newGraph(url_list->size);
    graphBuilder(url_list, urlConnections);
    showGraph(urlConnections, 1);


    //printList(url_list);

	char c = getchar();
    putchar(c);

    //attempt PR lmao
    //int i = 0;
    //double diff = diffPR;
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
