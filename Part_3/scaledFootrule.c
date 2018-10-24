#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

float scaledFootRuleCalc(int c, int t, int p, int n);
float min = 1000000000;
void perm(int v[], int n, int i);
int t1[][2] = {
	{ 1,1 },
{ 2,3 },
{ 3,5 },
{ 4,4 },
{ 5,2 },
};
int t2[][2] = {
	{ 1,3 },
{ 2,2 },
{ 3,1 },
{ 4,4 },
};

int main() {

	int p[5] = { 1,2,3,4,5 };
	int * pv = malloc(sizeof(int) * 5);

	for (int c = 0; c < 5; c++) {
		printf("Rank: %d, url%d\n", t1[c][0], t1[c][1]);
	}

	int i, j;
	int n = 5;
	perm(p, 5, 0);

	printf("min: %.6f\n", min);
	char q;
	q = getchar();
	putchar(q);
	return 0;
}
float scaledFootRuleCalc(int c, int t, int p, int n) {
	printf("t[c] = %d    t = %d    p = %d    n = %d\n", c, t, p, n);
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
void perm(int v[], int n, int i) {

	/* this function generates the permutations of the array
	* from element i to element n-1
	*/
	int	j;

	/* if we are at the end of the array, we have one permutation
	* we can use (here we print it; you could as easily hand the
	* array off to some other function that uses it for something
	*/
	if (i == n) {
		//for (j = 0; j < n; j++) {
			//printf("%d ", v[j]);
			//sum for loop

		int numOfTs = 2;
		float sum = 0;
		for (int a = 0; a < numOfTs; a++) {

			int tSize = 0;
			if (a == 0) { tSize = 5; }
			else { tSize = 4; }

			int k;
			
			for (k = 0; k < tSize; k++) {
				int biggestT = 5;
				if (a == 0) {
					sum += scaledFootRuleCalc(t1[k][1], tSize, v[k], biggestT);
				}
				else {
					sum += scaledFootRuleCalc(t2[k][1], tSize, v[k], biggestT);
				}
			}
		}
		//printf("sum: %.6f\n", sum);
		if (sum < min) {

			min = sum;

		}
		//printf("\n");
	}
	else
		/* recursively explore the permutations starting
		* at index i going through index n-1
		*/
		for (j = i; j < n; j++) {

			/* try the array with i and j switched */

			swap(v, i, j);
			perm(v, n, i + 1);

			/* swap them back the way they were */

			swap(v, i, j);
		}
}
int factorial(int a) {
	if (a == 1) return 1;
	return a * factorial(a - 1);
}