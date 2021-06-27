#include <libc.h>
int main(int ac, char **av)
{
	int a = atoi(av[1]);
	printf("%d\n", a);
	return 0;
}