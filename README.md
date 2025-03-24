# ParallelNP

## Opis
Namen projekta je med seboj **primerjati** različne pristope vzporednega reševanja [NP-polnih problemov](./docs/PROBLEMS.md) z **različnimi programskimi jeziki** (c, go, julia).\
Programje služi reševanju NP-polnih problemov z naštetimi jeziki.\
Programje v celoti lahko uprabljamo z ukazi `make`, kar je naknadno opisano v [dokumentaciji](./docs/USAGE.md).

## Namestitev
Za zaganjanje programja, je najprej potrebno [namestiti zahtevano programsko opremo](./docs/SETUP.md). \
Dodatna razlaga o delovanju programja je na voljo v [dokumentaciji](./docs/EXPLAIN.md).

## Primer Izvajanja
![Test](./docs/partition_output.png)
*Rezultati izvajanja za **Partition Problem**.*
![Test](./docs/kk_output.png)
*Rezultati izvajanja za **Kamada Kawai algoritem**.*


Algoritem z zmagovalnim časom je označen z rumeno barvo, algoritem z najslabšim časom pa s svetlo rdečo.
Časovno ugodnejše rešitve so označene z zeleno barvo, medtem ko so časovno manj ugodne rešitve označene z rdečo barvo.
V primeru, da rešitev ni pravilna, je to označeno s svetlo vijolično barvo.

## Vprašanja
V katerih primerih je sploh uporabno imeti več niti, kot jih ponuja procesor?
Omeni zakaj sem dal več različnih primerov z različnimi velikostmi množic.
Kaj narediti pri KK algo, ko se zaloopa / vrednost postane tako majhna, da delta več ne spreminja koordinat (C)
Kaj je torej logičen in fizičen thread - (razlika).
Kako je lahko go napisan v golangu.
