/* input: a source text file to find a word in
 * output: the lines in which the word occurs
 */

#include <stdio.h>
#include <string.h>

#define LIM1 5000	//constraint on the file size
#define LIM2 1000	//constraint on the line size
#define LIM3 100	//constraint on the pattern size 

#define TOPRINT lineno ? printf("%d %s\n", linecount, line) : printf("%s\n", line)

int search(char s[], char w[]);

int main(int argc, char *argv[]) {
	int negate = 0, lineno = 0;
	char c;
	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
				case 'x':
					negate = 1;
					break;
				case 'n':
					lineno = 1;
					break;
				default:
					printf("invalid attribute\n");
					return 0;
			}
	char file[LIM1], line[LIM2];
	int ch, i = 0, n, j = 0, k, linecount = 0;
	while ((ch = getchar()) != EOF)
		file[i++] = ch;
	file[i] = '\0';
	n = i;
	for (i = 0; i < n; i++) {
		if (file[i] == '\n') {
			linecount++;
			line[j] = '\0';
			if (!negate && search(line, *argv))
				TOPRINT;
			else if (negate && !search(line, *argv))
				TOPRINT;
			for (k = 0; k < strlen(line); k++)
				line[k] = '\0';
			j = 0;
		}
		else
			line[j++] = file[i];
	}
	return 0;
}

int search(char s[], char w[]) {
	int slen = strlen(s), wlen = strlen(w);
	for (int i = 0; i < slen - wlen + 1; i++) {
		int j, count = 0;
		for (j = 0; j < wlen; j++)
			if (s[i + j] == w[j])
				count++;
		if (count == wlen)
			return 1;
	}
	return 0;
}
