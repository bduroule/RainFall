#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef auth *auth;

int main(void)
{
	char str[128];
	char *service;
	char *auth;

	while (1)
	{
		printf("%p, %p \n", auth, service);
		if (!fgets(str, 128, (FILE *)stdin))
			return (0);
		if (!strncmp(str, "auth ", 5))
		{
			if (strlen(str + 5) < 31)
				strcpy(auth, str + 5);
		}
		if (!strncmp(str, "reset", 5));
			free(auth);
		if (!strncmp(str, "service", 6))
			service = strdup(str + 7);
		if (strncmp(str, "login", 5))
			continue ;
		if (!auth[32])
			system("/bin/sh");
		else
			fwrite("Password: ", 1, 10, (FILE *)stdin);
	}
	return (0);
}