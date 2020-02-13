/* THE ULTIMATE STRING SORTER
 * input: a list of strings
 * output: the strings in the alphabetic order default
 * -n: for comparing appropriate strings numerically
 * -r: for reverse order
 * -f: considers upper and lower cases on parity
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 100
#define FILESIZE 10000

#define DECIDE(x, y) optn ? numeric(x, y) : alphabetic(x, y)
#define NEGATOR(x) optr ? !(x) : x
#define ISALPH(x) (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') ? 1 : 0
#define NORMALIZER(x) x >= 'a' && x <= 'z' ? x - 'a' + 'A' : x

int input();
void selectionSort(int n);
void swap(int i1, int i2);
int alphabetic(char *a, char *b);	//is a before b alphabetically
int numeric(char *a, char *b);	//is a before b numerically
void output(int n);

char *arr[MAXLINE];
char file[FILESIZE];

int optn = 0, optr = 0, optf = 0;	//the attribute control switches

int main(int argc, char *argv[]) {
	char ch;
	while (--argc > 0 && *(++argv)[0] == '-')
		while (ch = *++argv[0])
			switch(ch) {
				case 'n':
					optn = 1;
					break;
				case 'r':
					optr = 1;
					break;
				case 'f':
					optf = 1;
					break;
				default:
					printf("ERROR: illegal option\n");
					return 0;
			}
	int size;
	if((size = input()) < 0)
		return 0;
	selectionSort(size);
	output(size);
	return 0;
}

int input() {
	int ch, i = 0, j = 0, flag = 1;
	while ((ch = getchar()) != EOF) {
		if (i >= MAXLINE) {
			printf("ERROR: exceeds maximum number of lines.\n");
			return -1;
		}
		if (ch == '\n') {
			file[j++] = '\0';
			flag = 1;
			continue;
		}
		file[j++] = ch;
		if (flag == 1) {
			arr[i++] = file + j - 1;
			flag = 0;
		}
	}
	if (!flag)
		file[j] = '\0';
	return i;
}

void selectionSort(int n) {
	for (int i = 0; i < n; i++) {
		char *min = arr[i];
		int index = i;
		for (int j = i + 1; j < n; j++)
			if (NEGATOR(DECIDE(arr[j], min))) {
				min = arr[j];
				index = j;
			}
		swap(i, index);
	}
}

int alphabetic(char *a, char *b) {
	char ch1 = *a, ch2 = *b;
	if (optf && ISALPH(ch1) && ISALPH(ch2)) {
		ch1 = NORMALIZER(ch1);
		ch2 = NORMALIZER(ch2);
	}
	if (ch1 < ch2)
		return 1;
	else if (ch1 > ch2)
		return 0;
	else
		if (ch1 == '\0' && ch2 == '\0')
			return 1;
		else if (ch1 == '\0')
			return 1;
		else if (ch2 == '\0')
			return 0;
		else
			return alphabetic(a + 1, b + 1);
}

int numeric(char *a, char *b) {
	double anum = atof(a), bnum = atof(b);
	if (anum >= bnum)
		return 0;
	else
		return 1;
}

void swap(int i1, int i2) {
	char *temp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = temp;
}

void output(int n) {
	printf("\n");
	for (int i = 0; i < n; i++)
		printf("%s\n", arr[i]);
}
