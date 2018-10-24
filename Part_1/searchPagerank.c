#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pagerank.h"

void BubbleSortListPR(List l);
void BubbleSortListRV(List l);
List mergeList(List l1, List l2);
List fileToList(char* find);
void PRList(List list);

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
void PRList(List list) {
	FILE* fp = fopen("pagerankList.txt", "r");
	char str3[100];
	list->curr = list->head;
	while (list->curr != NULL) {
		while (fscanf(fp, "%s", str3) != -1) {
			char* strp = str3;
			removeNonLetters(strp);
			if (strcmp(strp, list->curr->url) == 0) {
				fscanf(fp, "%s", str3);
				fscanf(fp, "%s", str3);

				list->curr->val = atof(str3);
				break;
			}
			else {
				fscanf(fp, "%s", str3);
				fscanf(fp, "%s", str3);
			}
		}
		rewind(fp);
		list->curr = list->curr->next;
	}
	fclose(fp);
}
List fileToList(char* find) {

	FILE* fp = fopen("invertedIndex.txt", "r");
	char str[1000];
	List list = newList();
	//get the first line
	while (fgets(str, 1000, fp) != NULL) {
		char* word = strstr(str, find);
		//if the word we are looking for isn't in the line,
		if (word == NULL) {
			//go to the next line
			continue;
		}
		//We have found the word
		char* url1 = strstr(word, " ");
		//url1 points 2 the beginning of all the urls
		url1 = strstr(&url1[1], " "); //there is 2 space after the words
		//url2 points at the end of the first url
		char* url2 = strstr(&url1[2], " ");
		//While not the end of the line
		while (url2 != NULL) {
			//copy the url into theUrl
			char* theUrl = malloc(strlen(url1) - strlen(url2));
			theUrl = memcpy(theUrl, &url1[1], strlen(url1) - strlen(url2) - 1);
			theUrl[strlen(url1) - strlen(url2) - 1] = '\0';
			insertList(theUrl, list);//insert the url into a new list
			url1 = url2;//url1 point to the beginning of the next url
			url2 = strstr(&url2[1], " ");//url2 point to the end of the next url
		}
		fclose(fp);
		return list;
	}
	printf("Could not find the word");
	return NULL;
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
		if (inside == 0 && l1->size <= 30) {
			insertList(l2->curr->url, l1);
		}
		l2->curr = l2->curr->next;
	}
	deleteList(l2);
	return l1;
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