#include <stdio.h>
#include <stdlib.h>

int m = 0;

void p(char *format) {
	printf(format);
}

void n() {
	char	s[512];

	fgets(&(s[0]), 512, (FILE *)stdin);
	p(s);
	if (m == 16930116)
		system("/bin/cat /home/user/level5/.pass");
}

int main() {
	n();
	return (0);
}
