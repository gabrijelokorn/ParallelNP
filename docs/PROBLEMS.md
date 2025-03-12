# Predstavitev problemov
V tem dokumentu se bomo spoznali s tremi NP-polnimi problemi. To so 
- ***Partition Problem na eni veliki množici***,
- ***Partition problem na veliko malih množicah*** in
- ***Kamada-Kawai algoritem***. 

Reševali jih bomo v treh različnih programskih jezikih. To so 
- C, 
- Julia in 
- Golang. 

Za vsakega izmed jezikov pa bomo rešitev implementirali tako v **zaporednem** kot tudi v **vzporednem** programu - na različne načine.

V vseh prihodnjih podanih primerih bo `<xy>` predstavljal zaporedno identifikacijsko število testnega primera.

## 1. Big partition
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo eno samo množico, na kateri bomo izvedli ta algoritem.

Primer testne datoteke `/tests/partition/<xy>.json`:
```json
{
    "1": [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1]
}
```

Primer rešitve `/tests/partition/solutions/<xy>.json`:
```json
[ true ]
```

## 2. Small partitions
---
Partition problem spada v teorijo števil in računalniških znanosti, kjer je cilj ugotoviti, če za dano množico pozitivnih števil S, obstajata taki podmnožici _S1_ in _S2_, da so seštevki števil množice _S1_ in množice _S2_ enaki.
Uporabili bomo hkrati več majhnih množic, na katerih bomo izvedli ta algoritem.

Primer testne datoteke `/tests/partition/<xy>.json`:
```json
{
    "1": [1, 2, 3, 4, 5],
    "2": [6, 10],
    "3": [6, 7, 8, 9],
    "4": [6, 7, 8, 9, 10]
}
```
Primer rešitve `/tests/partition/solutions/<xy>.json`:
```json
[ false, false, true, false ]
```

## 3. Kamada-Kawai algoritem
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
    "K": 2,
    "epsilon": 0.001,
    "display": 5
}
```

V sledečih datotekah so prikazani rezultati izvajanja:

`/tests/kamada_kawai/solutions/coords<xy>.csv`:
```csv
1,1 // vozlišče A v prvem koraku
2,1 // vozlišče B v prvem koraku
3,1 // vozlišče C v prvem koraku

1,2
2,2
3,2

1,3
2,3 // vozlišče B v tretjem koraku
3,3

1,4
2,4
3,4 // vozlišče C v četrtem koraku
```

To je primer s tremi točkami, ki se je izvedel v štirih korakih. "Stanja" (v kolikih korakih je bil algoritem izveden) so med seboj ločena s praznimi vrsticami.