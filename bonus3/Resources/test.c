#include <libc.h>

int main(int ac, char **av) {
    char buff[64];
    int n = atoi(av[1]);

    printf("atoi av[1]: %d\n", n);
    buff[n] = 0;
    printf("buff[n] = \"%lu\"\n", sizeof(buff[n]));
    return 0;
}