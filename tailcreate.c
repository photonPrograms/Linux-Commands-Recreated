/* implementation of the tail command
 * including the -n argument
 * where n is a whole number
 */

#include <stdio.h>
#define MAXLINE 100
#define LINESIZE 500

char lines[MAXLINE][LINESIZE];

int input();
void tail(int n, int totlines);

int main(int argc, char *argv[]) {
	int n = 10;
	if (argc > 1) {
		n = 0;
		char *p = argv[1];
		while (*++p != '\0')
			n = n * 10 + (*p - '0');
	}
	tail(n, input());
}

int input() {
	int ch, i = 0, j = 0;
	while ((ch = getchar()) != EOF) {
		lines[i][j++] = ch;
		if (ch == '\n') {
			lines[i][j] = '\0';
			j = 0;
			i++;
		}
	}
	return i;
}

void tail(int n, int totlines) {
	for (int i = totlines - 1, j = 1; i >= 0 && j <= n; i--, j++)
		printf("%s", lines[i]);
}
