# Delovanje programja
- Programi v vseh jezikih in vseh pristopih (različne implementacije) berejo iste testne datoteke.
- Testne datoteke so shranjene v direktorijih `tests/partition`, in `tests/kamada_kawai`.
- Vsak program v svoj direktorij zapisuje rezultate v datoteke `<xy>.csv` / `<xy>.json`
- Z izbiro `make check` se rezultati izvajanja preverijo na podlagi rešitev v `tests/<algoritem>/solutions`.
- Po izvedbi `make check` lahko rezultate vidimo v datoteki `views/check.html`.
- V `views` najdemo tudi ostale izide izvajanja - videe, ki prikazujejo izvajanje Kamada-Kawai algoritma.
