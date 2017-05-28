#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>

typedef struct student {
	int stdnum;
	char name[10];
	student *next;
} student;

//--- memory management ---
student *student_head = NULL;
student *student_pool = NULL;
int student_cnt = 0;
int used_memory = 0;
int max_used_mem = 0;

//--- functions ---
student *Alloc_student(void);
void Free_student(student *ptr);
void Free_student_pool(void);
void Free_student_head(void);

void newstudent(void);
void printstudent(void);
void findstudent(void);
void deletestudent(void);

student *search(char *input, int *flag);
int strtoint(char *a);

int main() {
	char input;
	int endflag = 0;
	while (1) {
		printf("--- Student management ---\n");
		printf(" 1. Register new student\n");
		printf(" 2. All student list\n");
		printf(" 3. Find a student\n");
		printf(" 4. Expel a student\n");
		printf(" 5. Exit\n");
		printf("--------------------------\n");
		input = _getch();

		switch (input) {
		case '1':
			newstudent();
			break;
		case '2':
			printstudent();
			break;
		case '3':
			findstudent();
			break;
		case '4':
			deletestudent();
			break;
		case '5':
			Free_student_pool();
			Free_student_head();
			endflag++;
			break;
		default:
			printf("Wrong input\n\n");
			break;
		}

		if (endflag)	break;
	}

	printf("\n");
	if (used_memory != 0)
		printf("There exist some nodes that are not freed\n");
	else
		printf("All memory freed\n");
	printf("Max used Memory : %d\n", max_used_mem);

	return 0;
}


student *Alloc_student(void) {
	student *ptr;
	if (student_pool != NULL) {
		ptr = student_pool;
		student_pool = student_pool->next;
	}
	else {
		ptr = (student*)malloc(sizeof(student));
		used_memory++;
		max_used_mem++;
	}

	student_cnt++;
	ptr->stdnum = 0;
	//	ptr->name = '\0';	how can I initialize the name..?
	ptr->next = NULL;

	return ptr;
}

void Free_student(student *ptr) {
	ptr->next = student_pool;
	student_pool = ptr;
	student_cnt--;
	return;
}

void Free_student_pool(void) {
	student *ptr;
	while (student_pool != NULL) {
		ptr = student_pool;
		student_pool = student_pool->next;
		free(ptr);
		used_memory--;
	}
	return;
}

void Free_student_head(void) {
	student *ptr;
	while (student_head != NULL) {
		ptr = student_head;
		student_head = student_head->next;
		free(ptr);
		used_memory--;
	}
	return;
}

void newstudent(void) {
	char *stuname;
	int stunum;
	student *ptr;

	while (1) {
		printf("\n *** Name : ");
L:		stuname = (char*)calloc(15, sizeof(char));
		fgets(stuname, 15, stdin);
		if (stuname[13] != '\0') {
			do {
				stunum = getchar();
			} while (stunum != EOF && stunum != '\n');
		}
		if (*stuname == '\n') {
			goto L;
			free(stuname);
		}
		else if (strlen(stuname) > 10 || strlen(stuname) < 2) {
			printf("     Name must be bigger than 2, shorter than 10\n");
			free(stuname);
		}
		else
			break;
	}
	stuname[strlen(stuname) - 1] = '\0';
	printf("     Student number : ");
	scanf_s("%d", &stunum);

	ptr = Alloc_student();
	ptr->stdnum = stunum;
	strcpy_s(ptr->name, stuname);

	if (student_head == NULL)
		student_head = ptr;
	else {
		student *pointer = student_head;
		while (pointer->next != NULL)
			pointer = pointer->next;
		pointer->next = ptr;
	}

	printf(" *** Registered! (name : %s, student num : %d)\n\n", ptr->name, ptr->stdnum);
	free(stuname);
	return;
}

void printstudent(void) {
	student *ptr;

	if (student_head == NULL) {
		printf("There's no students.\n\n");
		return;
	}

	printf("\n *** Student List\n");
	printf("     *name        *number\n");
	ptr = student_head;
	do {
		printf("     %-10s   %-6d\n", ptr->name, ptr->stdnum);
		ptr = ptr->next;
	} while (ptr != NULL);

	printf("\n");
	return;
}

void findstudent(void) {
	char *input;
	int flag = 2;
	int stunum;

	//flag  0 : error
	//		1 : find with student number
	//		2 : find with student name
	//		3 : found

	student *ptr = student_head;
	if (ptr == NULL) {
		printf("There's no student to find.\n\n");
		return;
	}

	do {
		stunum = getchar();
	} while (stunum != EOF && stunum != '\n');

	printf("\n");
	input = (char*)calloc(15, sizeof(char));
	printf(" *** Input the name or student number of the student : ");
	fgets(input, 15, stdin);
	if (input[13] != '\0') {
		do {
			stunum = getchar();
		} while (stunum != EOF && stunum != '\n');
	}

	input[strlen(input) - 1] = '\0';

	ptr = search(input, &flag);
	free(input);
	
	if (flag == 3)
		printf("     %6d  %10s\n\n", ptr->stdnum, ptr->name);
	else
		printf("     That student doesn't exist.\n\n");

	return;
}

void deletestudent(void) {
	char *input;
	int flag = 2;
	int stunum;

	//flag  0 : error
	//		1 : find with student number
	//		2 : find with student name
	//		3 : found

	student *ptr = student_head;
	if (ptr == NULL) {
		printf("There's no student to find.\n\n");
		return;
	}

	do {
		stunum = getchar();
	} while (stunum != EOF && stunum != '\n');

	printf("\n");
	input = (char*)calloc(15, sizeof(char));
	printf(" *** Input the name or student number of the student : ");
	fgets(input, 15, stdin);
	if (input[13] != '\0') {
		do {
			stunum = getchar();
		} while (stunum != EOF && stunum != '\n');
	}

	input[strlen(input) - 1] = '\0';

	ptr = search(input, &flag);
	free(input);

	//---------------------------------

	if (flag != 3) {
		printf("     That student doesn't exist\n\n");
		return;
	}

	printf("     Really delete %s (%d) 's data? (Y/N) : ", ptr->name, ptr->stdnum);
	char tmp = _getch();
	if (tmp == 'N')
		printf("\n     Canceled.\n\n");
	else if (tmp == 'Y') {
		if (ptr == student_head) {
			student_head = ptr->next;
			Free_student(ptr);
		}
		else {
			student *ptrprev = student_head;
			while (ptrprev != NULL) {
				if (ptrprev->next == ptr)
					break;
				ptrprev = ptrprev->next;
			}
			ptrprev->next = ptr->next;
//			ptr = ptr->next;
			Free_student(ptr);
		}
		printf("\n     Expel Completed.\n\n");
	}
	else
		printf("\n     Wrong input\n\n");

	return;
}

student *search(char *input, int *flag) {
	//Find the student node and returns it.
	//input is the name or number (string)
	int stunum;
	student *ptr = student_head;
	*flag = 2;

	if (strlen(input) > 10) {
		printf("     Wrong input\n\n");
		*flag = 0;
		return NULL;
	}
	if (*input > 47 && *input < 58) {		//number(student)
		stunum = strtoint(input);
		if (stunum < 0) {
			printf("     Wrong input\n\n");
			*flag = 0;
			return NULL;
		}
		*flag = 1;
	}

	if (*flag == 1) {
		//find with student number
		while (ptr != NULL) {
			if (ptr->stdnum == stunum) {
				*flag = 3;
				break;
			}
			ptr = ptr->next;
		}
	}
	else if (*flag == 2) {
		//find with student name
		while (ptr != NULL) {
			if (!strcmp(ptr->name, input)) {
				*flag = 3;
				break;
			}
			ptr = ptr->next;
		}
	}
	else {
		printf("     Coding Error\n\n");
		return NULL;
	}

	return ptr;
}

int strtoint(char *a) {
	int size = strlen(a);
	int tmp, result = 0;
	if (size <= 0)	return -1;

	for (int i = 0; i < size; i++) {
		tmp = a[i] - 48;
		if (tmp < 0 || tmp > 9)	return -1;
		result += pow(10, size - i - 1)*tmp;
	}

	return result;
}