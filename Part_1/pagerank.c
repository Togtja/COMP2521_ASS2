#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "queue.h"
#include "graph.h"
#include "pagerank.h"
#include <math.h>


void pageRankCalc(List l, double damp, double diffPR, int it);
float W_in(List l, struct node * src, struct node *p1);
float W_out(List l, struct node * src, struct node *p1);
List BubbleSortList(List l);
void printListToFile(List l, char* fileName);
//changes the pointer to lower
void stringToLower(char* str);
//removes ',' '.' ':' '?' from string
void removeNonLetters(char* str);

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

	List sort = BubbleSortList(url_list);
	printf("\nSORTED LIST:\n\n");
	printList(sort);
	printListToFile(sort, "pagerankList.txt");

	char * test = "TESTING; CAN. WE: LOWER_ IT?\n";
	char* ncnst = strdup(test);
	stringToLower(ncnst);
	printf("%s", ncnst);

	removeNonLetters(ncnst);
	printf("%s", ncnst);

	//free(test2);

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
    return 0;
}
List BubbleSortList(List l) {
	if (l->head == NULL || l->head->next == NULL || l->size <= 3) {
		printf("List is smaller 3 or less");
		return l;
	}
	List ret = copy(l);
	struct node * prv = NULL;
	struct node * cmp1 = ret->head;
	struct node * cmp2 = ret->head->next;
	int c;
	for (c = 0; c < ret->size * ret->size; c++) {
		if (cmp1->val < cmp2->val) {
			cmp1->next = cmp2->next;
			cmp2->next = cmp1;
			int ind = cmp1->pos;
			cmp1->pos = cmp2->pos;
			cmp2->pos = ind;
			if (prv == NULL) { ret->head = cmp2; }
			else {
				prv->next = cmp2;
			}

			prv = cmp2;
			cmp2 = cmp1->next;
		}
		else {
			prv = cmp1;
			cmp1 = cmp2;
			cmp2 = cmp2->next;
		}
		if (cmp2 == NULL) {
			prv = NULL;
			cmp1 = ret->head;
			cmp2 = ret->head->next;
		}
	}
	return ret;
}
void printListToFile(List l, char* fileName) {
	l->curr = l->head;
	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Something wrong happened\n");
		fclose(fp);
		return;
	}
	while (l->curr != NULL) {
		fprintf(fp, "%s, %d, %.7f\n", l->curr->url, l->curr->out, l->curr->val);
		l->curr = l->curr->next;
	}
	fclose(fp);
}
void pageRankCalc(List l, double damp, double diffPR, int it) {
	int i = 0; double diff = diffPR; l->curr = l->head;
	List temp = copy(l);

	temp->curr = temp->head;

	for (i = 0; i < it && diff >= diffPR; i++) {
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
//
void stringToLower(char *str) {
	char* s;
	for (s = str; *s; ++s) *s = *s >= 'A'&&*s <= 'Z' ? *s | 0x60 : *s;
}
//Author Fabio Cabral
//https://stackoverflow.com/questions/5457608/how-to-remove-the-character-at-a-given-index-from-a-string-in-c
void removeNonLetters(char *str) {
	char *src, *dst;
	for (src = dst = str; *src; src++) {
		*dst = *src;
		if (*dst != '.' &&
			*dst != ',' &&
			*dst != ';' &&
			*dst != '?') dst++;
	}
	*dst = '\0';
}
char* doTheThing(const char * str) {
	char* p = strdup(str);
	stringToLower(p);
	removeNonLetters(p);
	return p;

}

