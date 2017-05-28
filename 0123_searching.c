#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int sequential(char **input, char *key);
int binary(char **input, char *key);
int hash_init(char **input);
int hash(int hash_addr, char *key);

int main() {
	char *input[591];
	char *input_tmp = (char*)malloc(30 * sizeof(char));

	char key[7][16] = { "Abyssinian", "Boston Terrier", "Echidna",
		"Hummingbird", "Okapi", "Snapping Turtle", "Zorse" };

	clock_t start, end;
	float timecheck;

	printf("** Start input : input -> char array\n");
	start = clock();
	for (int i = 0; i < 591; i++) {
		int size = 0;
		fgets(input_tmp, 30, stdin);
		size = strlen(input_tmp);
		input_tmp[size - 1] = '\0';
		input[i] = (char*)malloc(size * sizeof(char));
		strcpy_s(input[i], size, input_tmp);
	}
	end = clock();
	timecheck = (float)(end - start) / CLOCKS_PER_SEC;
	printf("finished. (%.5lf ms)\n\n", timecheck);
	free(input_tmp);

	printf("** Start (1) sequential search\n");
	for (int i = 0; i < 7; i++) {
		int result;
		start = clock();
		result = sequential(input, key[i]);
		end = clock();
		if (i * 100 != result && (i == 0 && result != 0) && (i == 6 && result != 590)) {
			printf("--Wrong result! (error in %d)\n", i);
			return 0;
		}
		timecheck = (float)(end - start) / CLOCKS_PER_SEC;
		printf("%.5lf ms\t", timecheck);
	}
	printf("\n");
	printf("finished.\n\n");
	

	return 0;
}

int sequential(char **input, char *key) {
	char flag = 0;
	int i;
	for (i = 0; i < 591; i++) {
		if (!strcmp(input[i], key)) {
			flag = 1;
			break;
		}
	}

	if (flag)	return i;
	else		return -1;
}