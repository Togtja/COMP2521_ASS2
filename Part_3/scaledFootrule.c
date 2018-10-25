#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include "readData.h"

float scaledFootRuleCalc(int c, int t, int p, int n);
//int biggestT = 0;
void perm(int v[], int n, int i, List * lists, List unionL, int ts);
List listFromFile(char* file);
float min = 0;
//

int main(int argc, char* argv[]) {
	List listUnion = listFromFile(argv[1]);
	List * tList = malloc(sizeof(List) * (argc - 1));
	tList[0] = copy(listUnion);
	
	int i;
	for (i = 2; i < argc; i++) {
		List temp = listFromFile(argv[i]);
		tList[i - 1] = copy(temp);
		mergeList(listUnion, temp); //Frees temp
	}	
	int * p = malloc(sizeof(int) * listUnion->size);
	//Set the permutations of the list
	for (i = 0; i < listUnion->size; i++) {
		p[i] = i + 1;
	}
	//int v[5];
	//for (int i = 0; i<5; i++) v[i] = i + 1;
	min = (argc - 1) * listUnion->size; // Imposible to have a sum higher than this
	//(Assumes all list we send in is union size big, which is the "worst assumtion")

	perm(p, listUnion->size, 0, tList, listUnion, argc-1);

	printf("THE MIN IS:  %.6f ", min);

	char q;
	q = getchar();
	putchar(q);
	return 0;
}
float scaledFootRuleCalc(int c, int t, int p, int n) {
	//printf("t[c] = %d    t = %d    p = %d    n = %d\n", c, t, p, n);
	//printf("ret: %.6f\n", ret);
	return  fabs(((float)c / (float)t) - ((float)p / (float)n));
}

/* function to swap array elements */

void swap(int v[], int i, int j) {
	int	t;

	t = v[i];
	v[i] = v[j];
	v[j] = t;
}

/* recursive function to generate permutations */
void perm(int v[], int n, int i, List * lists, List unionL, int ts) {

	/* this function generates the permutations of the array
	* from element i to element n-1
	*/
	int	j;

	/* if we are at the end of the array, we have one permutation
	* we can use (here we print it; you could as easily hand the
	* array off to some other function that uses it for something
	*/
	if (i == n) {
		float sum = 0;
		//For each url in C
		unionL->curr = unionL->head; 
		//printf("\n\nNEW PERMETATION:\n\n");
		/*
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
						if (strcmp(unionL->curr->url, lists[j]->curr->url) == 0) {
							if (j == 0) {
								permute = v[p];
							}
							sum += scaledFootRuleCalc(lists[j]->curr->pos + 1, lists[j]->size, permute, n);
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

		}

		/*
		int a;
		for (a = 0; a < ts; a++) {

			int tSize = lists[a]->size;

			int k;
			for (k = 0; k < tSize; k++) {
				int biggestT = n;
				sum += scaledFootRuleCalc(k + 1, tSize, v[k], biggestT);
			}
		}
		//printf("sum: %.6f\n", sum);
		if (sum < min) {

			min = sum;

		}
		//printf("\n");*/
	}
	else
		/* recursively explore the permutations starting
		* at index i going through index n-1
		*/
		for (j = i; j < n; j++) {

			/* try the array with i and j switched */

			swap(v, i, j);
			perm(v, n, i + 1, lists, unionL, ts);

			/* swap them back the way they were */

			swap(v, i, j);
		}
}
int factorial(int a) {
	if (a == 1) return 1;
	return a * factorial(a - 1);
}

List listFromFile(char* file) {
	List list= newList();
	FILE* fp = fopen(file, "r");
	if (fp == NULL) {
		printf("FAILED TO OPEN FILE %d\n", file);
		exit(-1);
	}
	char str[100];
	while (fscanf(fp, "%s", str) != EOF) {
		insertList(str, list);
	}
	return list;
}