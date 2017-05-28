#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

#define MAX 1000
#define NA -1

//---FLOYD MATRIX---
int **D;
int **P;

//---DIJKSTRA MATRIX---
int *dist;
bool *sptSet;
int *prev;

//---FUNCTIONS (PRJ0208, FLOYD)---
void testresult(int i, int v);
void floyd(int v, int dirflag);
void path(int q, int r, int *flag);
//---FUNCTIONS (PRJ0303, DIJKSTRA)---
void dijk_main(int v, int start, int end);
bool sptTest(int v);
int distupdate(int v, int i);

//---ABOUT INPUT FILE---
//testcase
//vertex edge directed(=0, undirected=1)
//v1 v2 cost
//----------------------

int main() {
	FILE *fp;
	int testcase;
	int vertex, edge, dirflag, from, to, flag;

	fopen_s(&fp, "0208_input.txt", "r");
	fscanf_s(fp, "%d", &testcase);

	for (int i = 0; i < testcase; i++) {
		flag = 0;
		printf("*** Reading input file... ");
		fscanf_s(fp, "%d %d %d", &vertex, &edge, &dirflag);

		//--- allocate memory ---
		D = new int* [vertex];
		P = new int* [vertex];
		if (D == NULL || P == NULL) {
			printf("\n   malloc error\n");
			return -1;
		}
		for (int j = 0; j < vertex; j++) {
			D[j] = new int[vertex];
			P[j] = new int[vertex];
			for (int k = 0; k < vertex; k++) {	//initialize
				D[j][k] = MAX;
				P[j][k] = NA;
			}
		}
		for (int j = 0; j < vertex; j++)
			D[j][j] = 0;						//initialize

		//--- read input file ---
		for (int j = 0; j < edge; j++) {
			int tmp1, tmp2, tmp3;
			fscanf_s(fp, "%d %d %d", &tmp1, &tmp2, &tmp3);
			D[tmp1-1][tmp2-1] = tmp3;
			P[tmp1-1][tmp2-1] = tmp1;
			if (dirflag) {
				D[tmp2 - 1][tmp1 - 1] = tmp3;
				P[tmp2 - 1][tmp1 - 1] = tmp2;
			}
		}
		printf("\tCompleted.\n");

		//--- run floyd ---
		floyd(vertex, dirflag);

		//--- test results ---
		printf("    Testing the result... ");
		testresult(i, vertex);

		//--- find the path ---
		printf("    Which path do you want to find? from, to : ");
		fscanf_s(stdin, "%d %d", &from, &to);
		if (from < 0 || from >= vertex || to < 0 || to >= vertex) {
			printf("    Input error\n\n");
		}
		else {
			printf("    path (FLOYD)    : ");
			path(from, to, &flag);
			if (flag > 0 || from == to)	printf("%d\n", to);
			else						printf("none\n");
			printf("    path (DIJKSTRA) : \n");
			dijk_main(vertex, from, to);
			printf("\n");
		}
		
		//free memory
		for (int j = 0; j < vertex; j++) {
			delete[] D[j];
			delete[] P[j];
		}
		delete[] D;
		delete[] P;
		D = NULL;	P = NULL;
	}
	
	return 0;
}

void testresult(int i, int v) {
	if (i == 0) {
		int test[5][5] = { 0, 1, -3, 2, -4,
						3, 0, -4, 1, -1,
						7, 4, 0, 5, 3,
						2, -1, -5, 0, -2,
						8, 5, 1, 6, 0 };
		for (int j = 0; j < v; j++) {
			for (int k = 0; k < v; k++) {
				if (test[j][k] != D[j][k])
					printf("\n    D[%d][%d] is not %d but %d", j, k, test[j][k], D[j][k]);
			}
		}
	}

	else if (i == 2) {
		int test[4][4] = { 0, 5, 15, 10, 20, 0, 10, 5,
						30, 35, 0, 15, 15, 20, 5, 0 };
		for (int j = 0; j < v; j++) {
			for (int k = 0; k < v; k++) {
				if (test[j][k] != D[j][k])
					printf("\n    D[%d][%d] is not %d but %d", j, k, test[j][k], D[j][k]);
			}
		}
	}

	else if (i == 4) {
		int test[4][4] = { 0, 1, 2, 2, 1, 0, 1, 1,
						2, 1, 0, 1, 2, 1, 1, 0 };
		for (int j = 0; j < v; j++) {
			for (int k = 0; k < v; k++) {
				if (test[j][k] != D[j][k])
					printf("\n    D[%d][%d] is not %d but %d", j, k, test[j][k], D[j][k]);
			}
		}
	}
	
	printf("\tCompleted.\n");
	return;
}

void floyd(int v, int dirflag) {
	for (int k = 0; k < v; k++) {
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
//					P[i][j] = k;
					P[i][j] = P[k][j];
					if(dirflag)	P[j][i] = P[i][j];
				}
			}
		}
	}
	return;
}

void path(int q, int r, int *flag) {
	if (P[q][r] != -1) {
		path(q, P[q][r]-1, flag);
		printf("%d ", P[q][r]-1);
		(*flag)++;
//		path(P[q][r]-1, r);
	}
	return;
}


//------------------------------------
//-------------DIJKSTRA---------------
//------------------------------------

void dijk_main(int v, int start, int end) {
	int i = start;

	dist = (int*)malloc(v * sizeof(int));
	sptSet = (bool*)malloc(v * sizeof(bool));
	prev = (int*)malloc(v * sizeof(int));
	for (int j = 0; j < v; j++) {
		dist[j] = MAX;
		sptSet[j] = false;
		prev[j] = -1;
	}

	dist[start] = 0;
	sptSet[start] = true;

	while (!sptTest(v)) {
		printf("\nLet's start with i=%d\n", i);
		distupdate
	}

	free(dist);
	free(sptSet);
	free(prev);
	
	return;
}

bool sptTest(int v) {
	//If all sptSet is true, returns true.
	bool flag = true;
	for (int i = 0; i < v; i++) {
		if (sptSet[i])	continue;
		flag = false;
		break;
	}
	return flag;
}