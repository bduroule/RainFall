
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void	n()
{
	system("/bin/cat /home/user/level7/.pass");
}

void	m()
{
	puts("Nope");
}

int	main(int ac, char **av)
{
	void	*ptr1 = malloc(64);
	void	*ptr2 = malloc(4);

	ptr2 = m;
	strcpy(ptr1, av[1]);
	return 0;
}