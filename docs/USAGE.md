# Uporaba
## Makefile
Programje lahko prevedemo, zaganjamo in testiramo z uporabo Makefile datoteke v `src` direktoriju z ukazom `make`.

Zagon problema razdelitve z 1, 2, 4 nitmi (iz direktorija `src`):
```
clear && make -s clean && make -s pp R=1 THREADS="1 2 4" check 
```
Zagon risanja neusmerjenih grafov z 1, 2, 4 nitmi (iz direktorija `src`):
```
clear && make -s clean && make -s kk R=1 THREADS="1 2 4" check 
```
Risanje grafov (iz direktorija `src`):
```
make kamada_kawai
```

Zaganjanje `make`
```make
make
```
je ekvivalentno:
```make
make clean compile run check
```

Na voljo pa imamo tudi nekaj drugih možnosti:
| Ukaz | Efekt |
| --- | --- |
| `make clean` | _Izbriše vse datoteke, ki so nastale ob izvajanju programov._ |
| `make compile` | _Prevede vse programe v vseh jezikih._ |
| `make run` | _Vse programe zažene, pri čemer se v datoteke izpišejo rezultati izvajanja in časi izvajanja._ |
| `make check` | _Preveri izide izvajanja programov in jih zapiše v datoteko `/views/checks.js`._ |
| `make c` | _Prevede in zažene programe napisane v jeziku C._ |
| `make go` | _Prevede in zažene programe napisane v jeziku Golang._ |
| `make julia` | _Zažene programe napisane v jeziku Julia._ |
| `make clean` | _Izbriše vse datoteke, ki so nastale ob izvajanju programov._ |
| `make kamada_kawai` | _Generira videe za Kamada-Kawai algoritem._ |
