int	main(int ac, char **av)
{
	char	buf[128];
	int	fd;

	fd = fopen("/home/user/end/.pass", "r");
	bzero(&(buf[0]), 128);
	if (!fd || ac != 2)
		return (-1);
	fread(&(buf[0]), 1, 66, fd);
	buf[65] = '\0';
	buf[atoi(av[1])] = 0;
	fread(&(buf[66]), 1, 65, fd);
	fclose(fd);
	if (!strcmp(buf, av[1]))
		execl("/bin/sh", "sh");
	return (puts(&(buf[66])));
}