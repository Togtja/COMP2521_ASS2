#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "pagerank.h"
/*
printf("\nCAN WE FIND MARS:\n\n");
List list = findInBSTree(t, "mars");
if (list == NULL) printf("FAKE NEWS\n");
else printList(list);


List findInBSTree(BSTree t, char* str) {
	if (t == NULL) {
		return NULL;
	}
	char* search = normalise(str);
	if (strcmp(search, t->key) == 0) {
		printf("WE FOUND IT!!!");
		return t->urlList;
	}
	free(search);
	List ret = findInBSTree(t->left, str);
	if (ret != NULL) {
		return ret;
	}
	return findInBSTree(t->right, str);
}*/
void BubbleSortListPR(List l);
void BubbleSortListRV(List l);
List mergeList(List l1, List l2);
List fileToList(char* find);
void PRList(List list);

int main(int argc, char* argv[]) {

	char* find[] = {
		"mars",
		"japan",
		"intelligent",
	};
	int c = 3;
	int i;
	List* list = malloc(c * sizeof(List));
	for (i = 0; i < c; i++) {
		list[i] = fileToList(find[i]);
		printf("\nDOES IT WORK\n\n");
		printList(list[i]);
	}
	List cmp = list[0];
	for (int i = 1; i < c; i++) {
		cmp = mergeList(cmp, list[i]);
	}
	//DELETE LIST OF LIST
	printf("\n\nMERGED: \n");
	printList(cmp);

	printf("\n\nSORTED??\n\n");
	PRList(cmp);
	BubbleSortListPR(cmp);
	BubbleSortListRV(cmp);
	//BubbleSortListRV(cmp);
	printList(cmp);
	//List list = fileToList(find);
	//List list2 = fileToList(find2);
	/*

	printList(list);
	printf("\n\nDIFFRENT\n\n");
	printList(list2);

	printf("\n\nMERGED: \n");
	mergeList(list, list2);
	printList(list);



	printf("\n\nValued: \n");
	PRList(list);
	printList(list);
	*/
	printf("\n\nSORTED??\n\n");
	//List list1 = BubbleSortListPR(list);
	//List list3 = BubbleSortListRV(list1);
	//printList(list3);
		
	


	char k = getchar();
	putchar(k);
	return 0;
}
void PRList(List list) {
	FILE* fp = fopen("pagerankList.txt", "r");
	int i; char str3[100];
	list->curr = list->head;
	while (list->curr != NULL) {
		while (fscanf(fp, "%s", str3) != NULL) {
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
		list->curr = list->curr->next;
	}
	fclose(fp);
}
List fileToList(char* find) {

	FILE* fp = fopen("invertedIndex.txt", "r");
	char str[1000];
	List list = newList();

	while (fgets(str, 1000, fp) != NULL) {
		char* word = strstr(str, find);
		if (word == NULL) {
			continue;
		}
		char* url1 = strstr(word, " ");
		url1 = strstr(&url1[1], " ");
		char* url2 = strstr(&url1[2], " ");
		while (url2 != NULL) {
			char* theUrl = malloc(strlen(url1) - strlen(url2));
			theUrl = memcpy(theUrl, &url1[1], strlen(url1) - strlen(url2) - 1);
			theUrl[strlen(url1) - strlen(url2) - 1] = '\0';
			insertList(theUrl, list);
			url1 = url2;
			url2 = strstr(&url2[1], " ");
		}
	}
	fclose(fp);
	return list;
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
			//add l2->curr to l1;
			insertList(l2->curr->url, l1);
		}
		l2->curr = l2->curr->next;
	}
	//Free l2;
	return l1;
}

void BubbleSortListPR(List ret) {
	if (ret->head == NULL || ret->head->next == NULL || ret->size <= 3) {
		printf("List is smaller 3 or less");
		return;
	}
	//List ret = copy(l);
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
	//return ret;
}
void BubbleSortListRV(List ret) {
	if (ret->head == NULL || ret->head->next == NULL || ret->size <= 3) {
		printf("List is smaller 3 or less");
		return;
	}
	//List ret = copy(l);
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
	//return ret;
}