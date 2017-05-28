#include<stdio.h>
#include<stdlib.h>

//--- input format ---
//upperbound W, number of items
//weight0 profit0
//weight1 profit1
//weight2 profit2 ...

float **P;

//--- functions ---

#define IN
#define OUT
float knapsack_fractional(IN float *w, IN float *p, IN int n, IN float W, OUT float *flag);
void selectionsort(IN float *a, IN OUT int *index);
float knapsack_01(IN float *w, IN float *p, IN int n, IN float W, OUT float *flag);

int main() {
	int itemnum;
	float W, W_result;
	float *weight, *profit, *flag;
	char *filename = (char*)malloc(20 * sizeof(char));
	FILE *fp;

	printf("** Input file name : ");
	scanf_s("%s", filename, 20);
	fopen_s(&fp, filename, "r");
	if (!fp) {
		printf("   File open error\n");
		return 0;
	}

	fscanf_s(fp, "%f %d", &W, &itemnum);
	weight = (float*)malloc(itemnum * sizeof(float));
	profit = (float*)malloc(itemnum * sizeof(float));
	flag = (float*)calloc(itemnum, sizeof(float));
	for (int i = 0; i < itemnum; i++)
		fscanf_s(fp, "%f %f", &weight[i], &profit[i]);

	printf("\n** fractional knapsack\n");
	printf("   weights of each item :\n");
	W_result = knapsack_fractional(weight, profit, itemnum, W, flag);
	for (int i = 0; i < itemnum; i++) {
		printf("\t%.1f", flag[i]);
		if (flag[i] != weight[i])
			printf("(%.2f %%)", (flag[i] / weight[i]) * 100);
	}
	printf("   total weight = %.1f / %.1f\n\n", W_result, W);

	for (int i = 0; i < itemnum; i++)
		flag[i] = 0;

	printf("** 0-1 knapsack\n");
	printf("   1 : in bag / 0 : not in bag\n");
	W_result = knapsack_01(weight, profit, itemnum, W, flag);
	for (int i = 0; i < itemnum; i++)
		printf("\t%.0f", flag[i]);
	printf("   total weight = %.1f / %.1f\n\n", W_result, W);

	return 0;
}

float knapsack_fractional(IN float *w, IN float *p, IN int n, IN float W, OUT float *flag) {
	float *perunit = (float*)malloc(n * sizeof(float));
	int *index = (int*)malloc(n * sizeof(int));
	int weight = 0;

	for (int i = 0; i < n; i++) {
		perunit[i] = p[i] / w[i];
		index[i] = i;
	}
	selectionsort(perunit, index);
	//not ordering 'perunit' array, but only ordering 'index' array.
	//ex) perunit : 3 1 5 4 2
	//    index   : 1 4 0 3 2 (nth item, ordered)

	for (int i = 0; i < n; i++) {
		if (weight + w[index[i]] > W) {
			//cannot more adding, so slice it
			flag[index[i]] = w[index[i]] - (W - weight);
			weight = W;
			break;
		}
		flag[index[i]] = w[index[i]];
		weight += w[index[i]];
		if (weight == W)
			break;
	}

	return weight;
}

void selectionsort(IN float *a, IN OUT int *index) {
	return;
}


float knapsack_01(IN float *w, IN float *p, IN int n, IN float W, OUT float *flag) {
	return 0;
}