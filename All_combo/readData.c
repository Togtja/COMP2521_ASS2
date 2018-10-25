#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "graph.h"
#include "posix.h"

//comments in the header

List newList() {
    List list = malloc(sizeof(struct List));
    list->head = NULL;
    list->curr = NULL;
    list->graph = NULL;
    list->size = 0;
    return list;
}

void printList(List l) {

	l->curr = l->head; int i = 0;
    while (l->curr != NULL && i < 30) {
		printf("%s\n", l->curr->url);
		l->curr = l->curr->next; i++;
    }
}

void printOnlyUrls(List L) {

    struct node *ptr = L->head;
    while (ptr != NULL) {
        printf("%s ", ptr->url);
        ptr = ptr->next;
    }
    printf("\n");

}

void fprintOnlyUrls(List L, FILE *fp) {


    BubbleSortListSC(L);
    struct node *ptr = L->head;
    while (ptr != NULL) {
        fprintf(fp, "%s ", ptr->url);
        ptr = ptr->next;
    }
    fprintf(fp, "\n");

}



void insertList(char str[], List L) {
    struct node *link = malloc(sizeof(struct node));
    link->url = malloc(strlen(str) * sizeof(char) + 1);
    strcpy(link->url, str);
    link->next = NULL;
    if (L->head == NULL) {
        L->head = link;
        L->curr = L->head;
        L->head->pos = 0;
        L->head->in = 0;
        L->head->out = 0;
		L->head->val = 0;
		L->head->rankVal = 0;
    } else {
		L->curr = L->head;
		while (L->curr->next != NULL) {
			L->curr = L->curr->next;
		}
        L->curr->next = link;
        L->curr = L->curr->next;
        L->curr->pos = L->size;
        L->curr->in = 0;
        L->curr->out = 0;
		L->curr->val = 0;
		L->curr->rankVal = 0;
    }

    L->size++;
}

void listOfUrls(char file[], List l){
	//Find the file
    char * filename = malloc(strlen(file) + strlen(".txt") + 1);
    strcpy(filename, file);
    strcat(filename,".txt");
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "error: file collection.txt can not open\n");
        //return 0;
    }

    char str[10];

    //Queue q = newQueue();
    while(fscanf(fp, "%s", str) != EOF) {
        //printf("hey %s\n", str);
        insertList(str,l);
      //  QueueJoin(q, str);
    }

    fclose(fp);
    free(filename);
    //return q;
	//Make a list (Queue/Stack) of the URLS
	//Return the URL list
}



void graphBuilder(List urls, Graph g) {
	//Create an empty list
	//Get first element of the list
	//While list is not empt
    urls->curr = urls->head;
    addVertex(urls->curr->url, g->vertex, g->nV);
	g->nV++;

    while (urls->curr != NULL && nVertices(g) <= urls->size) {

        char *url_name = malloc(strlen(urls->curr->url) + strlen(".txt") + 1);
        strcpy(url_name, urls->curr->url);
        strcat(url_name, ".txt");

        FILE *fp = fopen(url_name, "r");

        if (fp == NULL) {
            printf("Could not fine file: %s\n", url_name);
			fclose(fp);
			free(url_name);
			urls->curr = urls->curr->next;
			continue;
        }
        //later gator
        char str[100];

        while (fscanf(fp, "%s", str) != EOF) {

            if (strstr(str, "Section-1") || strstr(str, "#start")) {
                continue;
            }

            if (strstr(str, "#end")) {
                break;
            }

            if(!isConnected(g, urls->curr->url, str) && strcmp(urls->curr->url, str) != 0) {
                addEdge(g, urls->curr->url, str);
				urls->curr->out++;
                struct node *finder = urls->head;
                while (strcmp(finder->url, str) != 0) {
                    finder = finder->next;
                }
                finder->in++;
            }

        }

        fclose(fp);
        free(url_name);

		urls->curr = urls->curr->next;
    }}

void initPR(List l) {
	l->curr = l->head;
	while (l->curr != NULL) {
		l->curr->val = 1.f/ (float)l->size;
		l->curr = l->curr->next;
	}
}
void add(List l,struct node * newN) {
	if (l->head == NULL) {
		l->head = newN;
	}
	else {
		l->curr = l->head;
		while (l->curr->next != NULL) {
			l->curr = l->curr->next;
		}
		l->curr->next = newN;
	}
	l->size++;
}
List copy(List l) {
	List cpy = newList();
	l->curr = l->head;
	while (l->curr != NULL) {
		struct node *newN = malloc(sizeof(struct node));
		newN->next = NULL;
		newN->pos = l->curr->pos;
		newN->in = l->curr->in;
		newN->out = l->curr->out;
		newN->val = l->curr->val;
		newN->rankVal= l->curr->rankVal;
		newN->url = nStrdup(l->curr->url);
		l->curr = l->curr->next;
		add(cpy, newN);
	}
	l->curr = l->head;
	return cpy;
}

void deleteList(List l) {
	l->curr = l->head;
	while (l->curr != NULL) {
		struct node* remv = l->curr;
		l->curr = l->curr->next;
		free(remv->url);
		free(remv);
	}
	if (l->graph != NULL) {
        disposeGraph(l->graph);
	}
	free(l);
}
void BubbleSortListPR(List ret) {
	if (ret == NULL) {
		printf("NULL list");
		return;
	}
	if (ret->size == 1) {
		printf("List is 1");
		return;
	}
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
}
void BubbleSortListRV(List ret) {
	if (ret == NULL) {
		printf("NULL list");
		return;
	}
	if (ret->size == 1) {
		printf("List is 1");
		return;
	}
	struct node * prv = NULL;
	struct node * cmp1 = ret->head;
	struct node * cmp2 = ret->head->next;
	int c;
	for (c = 0; c < ret->size * ret->size; c++) {
		if (cmp1->rankVal < cmp2->rankVal) {
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
}

void BubbleSortListSC(List ret) {
	if (ret == NULL) {
		//printf("NULL list");
		return;
	}
	if (ret->size == 1) {
		//printf("List is 1");
		return;
	}
	struct node * prv = NULL;
	struct node * cmp1 = ret->head;
	struct node * cmp2 = ret->head->next;
	int c;
	for (c = 0; c < ret->size * ret->size; c++) {
		if (strcmp(cmp1->url, cmp2->url) > 0) {
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
List mergeList(List l1, List l2) {
	l2->curr = l2->head;
	while (l2->curr != NULL) {
		l1->curr = l1->head;
		int inside = 0;
		while (l1->curr != NULL) {
			if (strcmp(l1->curr->url, l2->curr->url) == 0) {
				l1->curr->rankVal++;
				inside = 1;
				break;
			}
			l1->curr = l1->curr->next;
		}
		if (inside == 0) {
			insertList(l2->curr->url, l1);
		}
		l2->curr = l2->curr->next;
	}
	deleteList(l2);
	return l1;
}
