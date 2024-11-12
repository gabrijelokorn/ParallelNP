# ParallelNP

V tem dokumentu se bomo spoznali s tremi NP-polnimi problemi. To so 
- ***Partition Problem na eni veliki množici***,
- ***Partition problem na veliko malih množicah*** in
- ***Kamada-Kawai algoritem***. 

Reševali jih bomo v treh različnih programskih jezikih. To so 
- C, 
- Julia in 
- Golang. 

Za vsakega izmed jezikov pa bomo rešitev implementirali tako v **zaporednem** kot tudi v **vzporednem** programu.



## Predstavitev problemov
V vseh prihodnjih podanih primerih bo `<xy>` predstavljal zaporedno identifikacijsko število testnega primera.

### 1. Big partition
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo eno samo množico, na kateri bomo izvedli ta algoritem.

Primer testne datoteke `tests/big_partition/<xy>.json`:
```json
{
    "1": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1]
}
```

Primer rešitve `c/big_partition/output<xy>.json`:
```json
[ true ]
```

### 2. Small partitions
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo hkrati več majhnih množic, na katerih bomo izvedli ta algoritem.

Primer testne datoteke `/tests/small_partitions/<xy>.json`:
```json
{
    "1": [1, 2, 3, 4, 5],
    "2": [6, 10],
    "3": [6, 7, 8, 9],
    "4": [6, 7, 8, 9, 10]
}
```
Primer rešitve `c/small_partitions/output<xy>.json`:
```json
[ false, false, true, false ]
```

### 3. Kamada-Kawai algoritem
---
Obravani grafi so povezani grafi, katerih vozlišča niso omejena (ležijo prosto, kjerkoli v ravnini) in robovi predstavljeni s polnimi črtami. V našem modelu ravnovesje predstavlja kvadratni sum razlik med željenimi razdaljami in dejanskimi razdaljami med vozlišči.\
Algoritem je podrobno opisan v [znanstvenem članku](./docs/document.pdf).\
_Simetrični graf odraža simetrične sisteme vzmeti._

Primer testne datoteke `/tests/kamada_kawai/<xy>.json`:
```json
{
    "coords": [
        {
            "x": 1,
            "y": 1
        },
        {
            "x": 1,
            "y": 2
        },
        {
            "x": 3,
            "y": 1
        }
    ],
    "edges": [
        {
            "source": 0,
            "target": 1
        },
        {
            "source": 1,
            "target": 2
        },
        {
            "source": 2,
            "target": 0
        }
    ],
    "k": 1.5
}
```

V sledečih datotekah so prikazani rezultati izvajanja:

`points<xy>.csv`
```
3 - število vozlišč
```

`coords<xy>.csv`:
```
1,1 - vozlišče A v prvem koraku
2,1 
3,1

1,2
2,2
3,2

1,3
2,3 - vozlišče B v tretjem koraku
3,3

1,4
2,4
3,4 - vozlišče C v četrtem koraku
```

`edges<xy>.csv`:
```
1,2 - povezava med vozliščem A in B
2,3
```

To je primer s tremi točkami, ki se je izvedel v štirih korakih. "Stanja" (v kolikih korakih je bil algoritem izveden) so med seboj ločena s praznimi vrsticami.

## Uporaba
Programje lahko prevedemo, zaganjamo in testiramo z uporabo Makefile datoteke v korenskem direktoriju z ukazom `make`.

Zaganjanje samo `make` je enako kot:
```make
make compile run check
```

Na voljo pa imamo tudi nekaj drugih možnosti:
| Ukaz | Efekt |
| --- | --- |
| `make compile` | _Prevede vse programe v vseh jezikih._ |
| `make run` | _Vse programe zažene, pri čemer se v datoteke izpišejo rezultati izvajanja in časi izvajanja._ |
| `make c` | _Prevede in zažene programe napisane v jeziku C._ |
| `make julia` | _Prevede in zažene programe napisane v jeziku Julia._ |
| `make go` | _Prevede in zažene programe napisane v jeziku Golang._ |
| `make clean` | _Izbriše vse datoteke, ki so nastale ob izvajanju programov._ |
| `make kamada_kawai` | _Generira videe za Kamada-Kawai algoritem._ |
| `make check` | _Preveri izide izvajanja programov._ |


## Delovanje programja
- Programi v vseh jezikih in obeh pristopih (zaporedno in vzporedno) berejo iste testne datoteke.
- Testne datoteke so shranjene v direktorijih `tests/big_partition`, `tests/small_partitions` in `tests/kamada_kawai`.
- Vsak program v svoj direktorij zapisuje rezultate v datoteko `s<xy>.csv` / `s<xy>.json` za zaporedne program in `p<xy>.csv` / `p<xy>.json` za vzporedne programe.
- Z izbiro `make check` se rezultati izvajanja preverijo na podlagi rešitev v `tests/<algoritem>/solutions`.
- Po izvedbi `make check` lahko rezultate vidimo v datoteki `views/check.html`.
- V `views` najdemo tudi ostale izide izvajanja - videe, ki prikazujejo izvajanje Kamada-Kawai algoritma.