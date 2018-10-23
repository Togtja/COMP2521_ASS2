#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"
#include "pagerank.h"
#include <math.h>

//`void pageRanker(double d, double diffPR, double maxIterations, List urls, Graph g) {



//}
void pageRankCalc(List l, double damp, double diffPR, int it);
float W_in(List l, struct node * src, struct node *p1);
float W_out(List l, struct node * src, struct node *p1);


int main(int argc, char *argv[]) {


    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    printf("%lf, %lf, %d\n", d, diffPR, maxIterations);

    //build list of urls
    List url_list = newList();
    listOfUrls("collection", url_list);
	initPR(url_list);

	printList(url_list);


    //build a list of the page ranks of each url
    //and set them all to 1/N, N being num of urls


    //build a graph representation of the connections
    //between urls
	url_list->graph = newGraph(url_list->size);
    graphBuilder(url_list, url_list->graph);

    showGraph(url_list->graph, 1);

	pageRankCalc(url_list, d, diffPR, maxIterations);
    printList(url_list);

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
void pageRankCalc(List l, double damp, double diffPR, int it) {
	int i = 0; double diff = diffPR; l->curr = l->head;
	List temp = copy(l); //This dosen't really work
  //  printf("HI\n");

	temp->curr = temp->head;

	for (i = 0; i < it && diff >= diffPR; i++) {
		while (l->curr != NULL) {
			float sum = 0;
			for (temp->curr = temp->head; temp->curr != NULL; temp->curr = temp->curr->next) {
				if (l->graph->edges[temp->curr->pos][l->curr->pos]) {
					sum += temp->curr->val * W_in(l, temp->curr, l->curr) * W_out(l, temp->curr, l->curr);
//				    printf("sum %.7f\n", sum);
                }
			}


			l->curr->val = ((float) (1 - damp) / (float) l->size) + damp * sum;
//			printf("%.7f\n", l->curr->val);
            int j;
			temp->curr = temp->head;
			struct node * oldCurL = l->head; double sum1 = 0;
			for ( j = 0; oldCurL != NULL || temp->curr != NULL; j++) {
				sum1 += fabs(oldCurL->val - temp->curr->val);
				//printf("cur val: %.7f old val: %.7f sum1: %.7f", oldCurL->val, temp->curr->val, sum1);
                temp->curr = temp->curr->next;
				oldCurL = oldCurL->next;
			}
			diff = sum1;
			//abs(diff);


			l->curr = l->curr->next;
			//abs();
		}
//		printf("diff : %.7f\ndiffRP: %.7f\n\n", diff, diffPR);

		free(temp);
		temp = copy(l);
		l->curr = l->head;
		temp->curr = temp->head;
	}
}

float W_in(List l, struct node * src, struct node *p1) {
	int i = 0; float sum = 0;
	l->curr = l->head;
	for (i = 0; i < l->graph->nV; i++) {
		if (l->graph->edges[src->pos][i]) {
			sum += l->curr->in;
            //printf("%s %df\n", l->curr->url, l->curr->in);
		}
		l->curr = l->curr->next;
	}
	l->curr = p1;
    //printf("W In sum: %.7f\n", sum);
	return p1->in / (sum);

}
float W_out(List l, struct node * src, struct node *p1) {
	int i = 0; float sum = 0;
    //if (p1->out == 0) {
    //    sum = 0.5;
    //}
	l->curr = l->head;
	for (i = 0; i < l->graph->nV; i++) {
		if (l->graph->edges[src->pos][i]) {
			if (l->curr->out == 0) {
				sum += 0.5;
			}
			else{
				sum += l->curr->out;
			}
 //           printf("%s %d\n", l->curr->url, l->curr->out);

		}
		l->curr = l->curr->next;
	}
	l->curr = p1;
   // printf("W out sum: %.7f\n", sum);
	if (p1->out == 0) {
		return 0.5/sum;
	}
	return p1->out / (sum);
}
