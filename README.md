# ParallelNP

## Opis
Namen projekta je med seboj **primerjati** različne pristope vzporednega reševanja [problemov](./docs/PROBLEMS.md) z **različnimi programskimi jeziki** - **c, go, julia**.\
Programje na GitHub-u služi le reševanju teh problemov z naštetimi jeziki.

## Uporaba Programja
Za zaganjanje programja, je najprej potrebno [namestiti zahtevano programsko opremo](./docs/SETUP.md). \
Programje v celoti lahko uprabljamo z ukazi `make`, kar je naknadno opisano v [dokumentaciji](./docs/USAGE.md).\
Dodatna razlaga o delovanju programja je na voljo v [dokumentaciji](./docs/EXPLAIN.md).

## Primer Izvajanja
*Rezultati izvajanja za **Partition Problem**:*
![Test](./docs/partition_output.png)
*Rezultati izvajanja za **Kamada Kawai algoritem**:*
![Test](./docs/kk_output.png)


Algoritem z zmagovalnim časom je označen z rumeno barvo, algoritem z najslabšim časom pa s svetlo rdečo.
Časovno ugodnejše rešitve so označene z zeleno barvo, medtem ko so časovno manj ugodne rešitve označene z rdečo barvo.
V primeru, da rešitev ni pravilna, je to označeno s svetlo vijolično barvo.

Za Kamada-Kawai algoritem se generirajo tudi `avi` datoteke, ki prikazujejo premikanje delcev:

![Look into docs directory for examples](./docs/kk1.gif)\
![Look into docs directory for examples](./docs/kk2.gif)

## Vprašanja
- Omeni zakaj sem dal več različnih primerov z različnimi velikostmi množic.
- Kako je lahko golang napisan v golangu.
- Problem pri simuliranem ohlajanju in omejevanju korakov: Namen tega je, da se ustavi po osciliranju. Kaj če oscilira, a to še ni zadnji delec, ki bi ga bilo potrebno premakniti?
- Zakaj je ob uporabi polovice niti zasedenih vseh n niti