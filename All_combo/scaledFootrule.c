#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "readData_SFR.h"

float scaledFootRuleCalc(int c, int t, int p, int n);
float perm(int v[], int n, int i, List_SFR * lists, List_SFR unionL, int ts, int* result, float min);
List_SFR listFromFile(char* file);
void copyArray(int *src, int*dest, int length);

int main(int argc, char* argv[]) {
	List_SFR listUnion = listFromFile(argv[1]);

	//Somehow this lose 16 bytes of memory
	List_SFR * tList = malloc(sizeof(List_SFR) * (argc - 1));
	tList[0] = copy_SFR(listUnion);
	int bigT = tList[0]->size;//set list 0 to be the biggest list (for now)
	int i;
	for (i = 2; i < argc; i++) {
		List_SFR temp = listFromFile(argv[i]);
		//if find bigger list, then set that as biggest list
		if (temp->size > bigT) bigT = temp->size;
		tList[i - 1] = copy_SFR(temp);
		mergeList_SFR(listUnion, temp); //Frees temp
	}
	int * p = malloc(sizeof(int) * bigT);
	int* result = malloc(sizeof(int) * listUnion->size);
	for (i = 0; i < listUnion->size; i++) {
		result[i] = i + 1;
	}
	//Set the permutations of the list
	for (i = 0; i < bigT; i++) {
		p[i] = i + 1;
	}
	//int v[5];
	//for (int i = 0; i<5; i++) v[i] = i + 1;
	float min = (argc - 1) * bigT; // Imposible to have a sum higher than this
	//(Assumes all list we send in has same size and is the biggest, which is the "worst assumtion")

	min = perm(p, bigT, 0, tList, listUnion, argc-1, result, min);


	printf("%.6f\n", min);
	for (i = 0; i < listUnion->size; i++) {
		listUnion->curr = listUnion->head;
		while (listUnion->curr != NULL) {
			if (listUnion->curr->pos == result[i] - 1) {
				printf("%s\n", listUnion->curr->url);
			}
			listUnion->curr = listUnion->curr->next;
		}

	}
	deleteList_SFR(listUnion);
	//I though this was correctly freeing the memory?
	for (i = 0; i < argc-1; i++) {
		deleteList_SFR(tList[i]);
	}
	free(p);
	free(result);
	return 0;
}
float scaledFootRuleCalc(int c, int t, int p, int n) {
	//printf("t[c] = %d    t = %d    p = %d    n = %d\n", c, t, p, n);
	return  fabs(((float)c / (float)t) - ((float)p / (float)n));
}

//function to swap array elements

void swap(int v[], int i, int j) {
	int	t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}

//recursive function to generate permutations
float perm(int v[], int n, int i, List_SFR * lists, List_SFR unionL, int ts, int*result, float min) {
	int	j;
	if (i == n) {
		float sum = 0;
		//For each url in C
		unionL->curr = unionL->head;
		/*
		printf("\n\nNEW PERMETATION:\n\n");

		for (int z = 0; z < n; z++) {
			printf("%d ", v[z]);
		}
		*/
		while (unionL->curr != NULL) {
			//printf("\nTHE URL %s IN C\n", unionL->curr->url);
			//For each of urls in lists
			//int j;
			int permute = 0;
			for (j = 0; j < ts; j++) {
				lists[j]->curr = lists[j]->head;
				int p = 0;
					while (lists[j]->curr != NULL) {
						if (j == 0) {
							permute = v[p];
						}
						if (strcmp(unionL->curr->url, lists[j]->curr->url) == 0) {

							sum += scaledFootRuleCalc(lists[j]->curr->pos + 1, lists[j]->size, permute, unionL->size);
							break;
						}
						p++;
						lists[j]->curr = lists[j]->curr->next;
					}
			}
			unionL->curr = unionL->curr->next;
		}

		if (sum < min) {
			min = sum;
			copyArray(v, result, n);
		}
	}
	else
		for (j = i; j < n; j++) {
			swap(v, i, j);
			min = perm(v, n, i + 1, lists, unionL, ts, result, min);
			swap(v, i, j);
		}
    return min;
}
List_SFR listFromFile(char* file) {
	List_SFR list= newList_SFR();
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("FAILED TO OPEN FILE %s\n", file);
		exit(-1);
	}
	char str[100];
	while (fscanf(fp, "%s", str) != EOF) {
		insertList_SFR(str, list);
	}
	fclose(fp);
	return list;
}
void copyArray(int* src, int* dest, int length) {
	int i;
	for (i = 0; i < length; i++) {
		dest[i] = src[i];
	}
}
