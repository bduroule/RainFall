### Level 0

Une fois connecter au level 0 on peut voir un binaire level0
``` 
level0@RainFall:~$ ls -l
total 732
-rwsr-x---+ 1 level1 users 747441 Mar  6  2016 level0
```
En l'ouvrant avec cutter on remarque que le main appelle atoi pour convertir notre argument et dans un segond temp le compare avec un nombre en hexadecimale qui est egale a 423. Il sufit donc dappler le programe avec 423 en argument pour rentre dans la condition qui nous donnera les droit.

```
level0@RainFall:~$ ./level0 423
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ 
```