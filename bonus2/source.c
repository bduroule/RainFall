int language = 0;

int greetuser(char *param1)
{
	char tmp[72];

	if (language == 1)
		memcpy(tmp, "Hyvää päivää ", 19);
	else if (language == 2)
		memcpy(tmp, "Goedemiddag! ", 14);
	else if (language == 0)
		memcpy(&(tmp[0]), "Hello ", 7);	
	strcat(tmp, param1);
	puts(tmp);
}

int main(int ac, char **av)
{
	char	buf2[72];
	char	buf[72];
	char	envvar;	

	if (ac != 3)
		return (1);
	bzero(&(buf2[0]), 72);			
	strncpy(&(buf[0]), av[1], 40);
	strncpy(&(buf[40]), av[2], 32);
	envvar = getenv("LANG");
	if (envvar != '\0')
	{
		if (!memcmp(envvar, "fi", 2))
			language = 1;
		else if (!memcmp(envvar, "nl", 2))
			language = 2;
	}
	memcpy(&(buf2[0]), &(buf[0]));		
	return (greetuser(&(buf2[0])));
}