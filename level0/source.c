#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int iVar1;
	char *uStack32;
	int uStack24;
	int uStack20;

	iVar1 = atoi(argv[1]);
	if (iVar1 == 423)
	{
		uStack32 = strdup("/bin/sh");
		uStack24 = geteuid();
		uStack20 = getegid();
		execv("/bin/sh", &uStack32);
	}
	else
	{
		fwrite("No !\n", 1, 5, (FILE *)stderr);
	}
	return 0;
}