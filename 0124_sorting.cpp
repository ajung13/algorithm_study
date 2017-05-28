#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define IN
#define OUT

void exchange(IN int *a, IN int size, OUT int *b);
void bubble(IN int *a, IN int size, OUT int *b);
void selection(IN int *a, IN int size, OUT int *b);
void insertion(IN int *a, IN int size, OUT int *b);
void merge_main(IN int *a, IN int size, OUT int *b);
void quick_main(IN int *a, IN int size, OUT int *b);

void mergesort(int *a, int low, int high);
void merge(int *a, int low, int mid, int high);
void quicksort(int *a, int low, int high);
void partition(int *a, int low, int high, int *pivotpoint);

int testsort(IN int *a, IN int size);
void swap(int *a, int *b);
void print(int *a, int size);


int main() {
	clock_t start, end;
	float timecheck;

	FILE *fp;
	char *filename = (char*)malloc(20 * sizeof(char));
	int *input;
	int size = 0, tmp;

	printf("Input file name (number only file) : ");
	scanf_s("%s", filename, 20);

	printf("\nRead %s...", filename);
	fopen_s(&fp, filename, "r");
	if (!fp) {
		printf("\nFile open error.\n");
		return 0;
	}
	while (!feof(fp)) {
		fscanf_s(fp, "%d", &tmp);
		size++;
	}
	rewind(fp);
	input = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++)
		fscanf_s(fp, "%d", &input[i]);
	fclose(fp);
	free(filename);
	printf("\tfinished.\n\n");

	//--------------------------------------------------

	printf("** Exchange sort ... ");
	int *exchangesort = (int*)malloc(size * sizeof(int));
	start = clock();
	exchange(input, size, exchangesort);
	tmp = testsort(exchangesort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(exchangesort);

	printf("** Bubble sort ... ");
	int *bubblesort = (int*)malloc(size * sizeof(int));
	start = clock();
	bubble(input, size, bubblesort);
	tmp = testsort(bubblesort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(bubblesort);

	printf("** Selection sort ... ");
	int *selectionsort = (int*)malloc(size * sizeof(int));
	start = clock();
	selection(input, size, selectionsort);
	tmp = testsort(selectionsort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(selectionsort);

	printf("** insertion sort ... ");
	int *insertionsort = (int*)malloc(size * sizeof(int));
	start = clock();
	insertion(input, size, insertionsort);
	tmp = testsort(insertionsort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(insertionsort);

	printf("** merge sort ... ");
	int *mergesort = (int*)malloc(size * sizeof(int));
	start = clock();
	merge_main(input, size, mergesort);
	tmp = testsort(mergesort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(mergesort);

	printf("** quick sort ... ");
	int *quicksort = (int*)malloc(size * sizeof(int));
	start = clock();
	quick_main(input, size, quicksort);
	tmp = testsort(quicksort, size);
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	if (!tmp)	printf("\tERROR : not sorted\n\n");
	else		printf("\tfinished (%.3f ms)\n\n", timecheck);
	free(quicksort);
	
	free(input);
	return 0;
}


int testsort(IN int *a, IN int size) {
	// input : integer array a, integer size
	// output : 1 or 0
	// If a is sorted, returns 1 and if not, returns 0.

	for (int i = 0; i < size - 1; i++) {
		if (a[i] > a[i + 1])	return 0;
	}
	return 1;
}

void swap(int *a, int *b) {
	//swap a and b
	int tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}

void print(int *a, int size) {
	//print all numbers in a array
	for (int i = 0; i < size; i++)
		printf("%5d ", a[i]);
	printf("\n");
	return;
}

void exchange(IN int *a, IN int size, OUT int *b) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (b[j] < b[i])	swap(&b[i], &b[j]);
		}
	}

	return;
}


void bubble(IN int *a, IN int size, OUT int *b) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];

	for (int i = size - 1; i > 0; i--) {
		for (int j = 0; j < size - 1; j++) {
			if (b[j] > b[j + 1]) 	swap(&b[j], &b[j + 1]);
		}
	}

	return;
}

void selection(IN int *a, IN int size, OUT int *b) {
	int max = 0;

	for (int i = 0; i < size; i++)
		b[i] = a[i];

	for (int i = size - 1; i > 0; i--) {
		max = 0;
		for (int j = 1; j <= i; j++) {
			if (b[j] > b[max])	max = j;
		}
		swap(&b[i], &b[max]);
	}

	return;
}

void insertion(IN int *a, IN int size, OUT int *b) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];

	for (int i = 1; i < size; i++) {	//range : 0 ~ i-1, and i <- new!
		for (int j = i; j > 0; j--) {
			if (b[j] < b[j - 1])	swap(&b[j], &b[j - 1]);
		}
	}

	return;
}

void merge_main(IN int *a, IN int size, OUT int *b) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];

	mergesort(b, 0, size - 1);

	return;
}

void quick_main(IN int *a, IN int size, OUT int *b) {
	for (int i = 0; i < size; i++)
		b[i] = a[i];

	quicksort(b, 0, size - 1);

	return;
}
 

void mergesort(int *a, int low, int high) {
	int mid;
	if (low < high) {
		mid = (low + high) / 2;
		mergesort(a, low, mid);
		mergesort(a, mid + 1, high);
		merge(a, low, mid, high);
	}
	return;
}

void merge(int *a, int low, int mid, int high) {
	int i, j, k;
	int *U = (int*)malloc((high+1) * sizeof(int));
	i = low;
	j = mid + 1;
	k = low;

	while (i <= mid && j <= high) {
		if (a[i] < a[j]) {
			U[k] = a[i];
			i++;
		}
		else {
			U[k] = a[j];
			j++;
		}
		k++;
	}

	if (i > mid) {
		for (int l = j; l <= high; l++)
			U[k + l - j] = a[l];
	}
	else {
		for (int l = i; l <= mid; l++)
			U[k + l - i] = a[l];
	}

	for (int l = low; l <= high; l++)
		a[l] = U[l];

	return;
}

void quicksort(int *a, int low, int high) {
	int pivotpoint;
	if (high > low) {
		partition(a, low, high, &pivotpoint);
		quicksort(a, low, pivotpoint - 1);
		quicksort(a, pivotpoint + 1, high);
	}
	return;
}

void partition(int *a, int low, int high, int *pivotpoint) {
	int i, j, pivotitem;
	j = low;
	pivotitem = a[low];

	for (i = low + 1; i <= high; i++) {
		if (a[i] < pivotitem) {
			j++;
			swap(&a[i], &a[j]);
		}
	}
	*pivotpoint = j;
	swap(&a[low], &a[*pivotpoint]);

	return;
}