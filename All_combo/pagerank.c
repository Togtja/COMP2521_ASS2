
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include <math.h>
#include "BSTree.h"
#include "invertedIndex.h"
#include "posix.h"


void pageRankCalc(List l, double damp, double diffPR, int it);
float W_in(List l, struct node * src, struct node *p1);
float W_out(List l, struct node * src, struct node *p1);

int main(int argc, char *argv[]) {

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    //printf("%lf, %lf, %d\n", d, diffPR, maxIterations);

    //build list of urls
    List url_list = newList();
    listOfUrls("collection", url_list);

	initPR(url_list);

    //build a list of the page ranks of each url
    //and set them all to 1/N, N being num of urls


    //build a graph representation of the connections
    //between urls
	url_list->graph = newGraph(url_list->size);

    graphBuilder(url_list, url_list->graph);


	pageRankCalc(url_list, d, diffPR, maxIterations);


	BubbleSortListPR(url_list);

	printListToFile(url_list, "pagerankList.txt");
	printf("FINSHIED\n");
    return 0;
}
void pageRankCalc(List l, double damp, double diffPR, int it) {
	int i = 0; double diff = diffPR; l->curr = l->head;


	for (i = 0; i < it && diff >= diffPR; i++) {
		List temp = copy(l);
		l->curr = l->head;
		temp->curr = temp->head;
		while (l->curr != NULL) {
			float sum = 0;
			for (temp->curr = temp->head; temp->curr != NULL; temp->curr = temp->curr->next) {
				if (l->graph->edges[temp->curr->pos][l->curr->pos]) {
					sum += temp->curr->val * W_in(l, temp->curr, l->curr) * W_out(l, temp->curr, l->curr);
                }
			}
			l->curr->val = ((1 - damp) /  l->size) + damp * sum;
            int j;
			temp->curr = temp->head;
			struct node * oldCurL = l->head; double sum1 = 0;
			for ( j = 0; oldCurL != NULL || temp->curr != NULL; j++) {
				sum1 += fabs(oldCurL->val - temp->curr->val);
                temp->curr = temp->curr->next;
				oldCurL = oldCurL->next;
			}
			diff = sum1;
			l->curr = l->curr->next;
		}
		//l->curr = l->head;
		deleteList(temp);

	}
}

float W_in(List l, struct node * src, struct node *p1) {
	int i = 0; float sum = 0;
	l->curr = l->head;
	for (i = 0; i < l->graph->nV; i++) {
		if (l->graph->edges[src->pos][i]) {
			sum += l->curr->in;
		}
		l->curr = l->curr->next;
	}
	l->curr = p1;
	return p1->in / (sum);

}
float W_out(List l, struct node * src, struct node *p1) {
	int i = 0; float sum = 0;
	l->curr = l->head;
	for (i = 0; i < l->graph->nV; i++) {
		if (l->graph->edges[src->pos][i]) {
			if (l->curr->out == 0) {
				sum += 0.5;
			}
			else{
				sum += l->curr->out;
			}

		}
		l->curr = l->curr->next;
	}
	l->curr = p1;
	if (p1->out == 0) {
		return 0.5/sum;
	}
	return p1->out / (sum);
}
