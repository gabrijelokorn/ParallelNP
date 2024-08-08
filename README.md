# ParallelNP

V tem dokumentu se bomo spoznali s tremi NP-polnimi problemi. To so Partition problem na eni veliki množici, Partition problem na veliko malih množicah in Fructerman Reingold algoritem. Reševali jih bomo v treh različnih programskih jezikih. To so C, Julia in Golang.

# Predstavitev problemov


## 1. Large partition
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici S_1 in S_2, da so seštevki števil množice S_1 in množice S_2 enaki.

## 2. Small partitions
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici S_1 in S_2, da so seštevki števil množice S_1 in množice S_2 enaki.

## 3. Fructerman Reingold algoritem
---

# Uporaba
Programje lahko prevedemo in začenemo z uporabo Makefile datoteke v korenskem direktoriju z ukazom `make`.

Prevod (priprava):
```make
make compile
```

Testiranje:
```make
make test
```

Čiščenje:
```make
make clean
```

Ob izvajanju oziroma testiranju se izpišejo rezultati in časi izvajanja programov. Rezultate vsakega izmed programov najdemo v direktoriju, kjer se nahaja program, v datoteki z imenom `output.txt`.

# Potek programa
- vsak program v svoj direktorij zapisuje rezultate v datoteko `output.txt`.