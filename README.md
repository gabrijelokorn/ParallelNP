# ParallelNP

V tem dokumentu se bomo spoznali s tremi NP-polnimi problemi. To so Partition problem na eni veliki množici, Partition problem na veliko malih množicah in Kamada-Kawai algoritem. Reševali jih bomo v treh različnih programskih jezikih. To so C, Julia in Golang.

## Predstavitev problemov


### 1. Big partition
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo eno samo množico, na kateri bomo izvedli ta algoritem.

### 2. Small partitions
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo hkrati več majhnih množic, na katerih bomo izvedli ta algoritem.

### 3. Kamada-Kawai algoritem
---
Algoritem je opisan v [documentu](./docs/document.pdf).

## Uporaba
Programje lahko prevedemo in zaganjamo z uporabo Makefile datoteke v korenskem direktoriju z ukazom `make`.

Zaganjanje samo `make` je enako kot:
```make
make compile run VERBOSE=1
```

Prevod (priprava):
```make
make compile
```

Zaganjanje:
```make
make run
```

Merjenje časa:
```make
make VERBOSE=0
```

Čiščenje:
```make
make clean
```

Ob izvajanju oziroma testiranju se izpišejo rezultati ali pa časi izvajanja programov.\
Rezultate vsakega izmed programov najdemo v direktoriju, kjer se nahaja program, v datoteki z imenom `output.txt`.\
Izpisane čase izvajanja najdemo v TODO .... \

## Delovanje programja
- vsak program v svoj direktorij zapisuje rezultate v datoteko `output<xy>.txt`.
- Programi so napisani tako, da se izvaja le potrebni del kode, kadar je izključena možnost `VERBOSE`. To pa zato, da dobimo kar se da zanesljive meritve časa.
