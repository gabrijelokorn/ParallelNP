# Kronološki zapsiki ob izdelavi diplomske naloge

12.02.2024
---
Po izpitu OUI (~13:00) sem šel v profesorjev kabinet. Omenil sem mu področja, ki me zanimajo. Profesor mi je podal par vprašanj v razmislek v povezavi s temo in naravo dela za diplomsko nalogo. Sam nisem imel nobene zamisli za specifični projekt, zato sem ga prosil, da mi priskrbi kakšno temo za diplomsko delo.

19.02.2024
---
Po predavanjih prevajalnikov (~17:00) sem se sestal s profesorjem glede teme. Profesor mi je pokazal osnovno o Julia programskem jeziku.

21.02.2024
---
Sestanek je bil v učinlici po vajah prevajalnikov (~09:00). Profesor mi je priskrbel temo. Zmenila sva se, da bi lahko primerajal vzporedno programiranje v različnih programskih jezikih na enakih problemih.  
Kandidati za jezike:
```
Go
c
C++
Julia
```
Kandidati za probleme:
```
NP-poln problem (partitioning problem)
Problem iz teorije grafov
HashTable problem ?
```
26.02.2024
---

Srečanje s profesorjem po predavanjih prevajalnikov. Obnovila sva, kar sva bila že zmenjena. Dokončno sva dorekla, da bodo problemi iz teorije grafov. Do prihodnjihkrat bova oba našla probleme na tem področju.

13.3.2024 Sestanek po vajah za prevajalnike 11:30 - 12:15
---

# ![Slika](timeline_1.png)  
S profesorjem sva našla tri algoritme iz teorije grafov, na katerih bom testiral vzporedno programiranje v treh različnih jezikih.

- 1. NP problem: "Partitioning problem" - velika množica
- 2. NP problem: "Partitioning problem" - veliko malih množic, ki jih generiramo s postopkom, ponazorjenem na sliki (graf na sredini zgoraj na [sliki](#slika))
- 3. Imena tretjega algoritma se nisva spomnila. Gre za algoritem, kjer imamo podan graf G<V,E>, pri čemer se vsako vozlišče z vsakim med seboj odbija (odbojna sila), le da se tisti, ki so med seboj povezani med seboj privlačijo (se držijo skupaj)

Do naslednjič si pogledam te algoritme in poskusim katerega izmed njih imlementirati.

Pri prvih dveh problemih bom rešitev poskusil implementirati rekurzivno kot tudi iterativno, da opazujemo kakšno "performance" ceno ima klic funkcije (preklapalanje med nitmi - menjava konteksta in podobno).

03.04.2024 Sestanek po vajah za prevajalnike 11:10 - 11:40
---

Pogovor sva začela s problemom, ki sva ga prejšnjikrat obdelala nekoliko manj podrobno - to je tretji problem oziroma problem simuliranja premikanja delcev, ki drug drugega bodisi privlačijo ali odbijajo.
Podrobnejši opis implementacije:

- Vozlišča problema bomo generirali naključno. Za generiranje vozlišč lahko načeloma uporabimo psevdonaključne algoritme, vendar bi bilo dobro, da pazim, da niti, ki uporabljajo enak algoritem za naključne koordinate (si ga delijo) prejmejo različna (dejansko naključna) števila.
- Zelo dobro bi bilo prikazati začetno in končno stanje grafa s sliko, zaporedjem slik (začetno in končno stanje) ali pa gifom. To je moč narediti v katerem koli jeziku (octave, Matlab ipd. je popolnoma vseeno kako to naredim). Že za sam prikaz uspešnosti rešitve in bolše tolmačenje pa je skoraj nujen ta prikaz.
- Ker lahko pride do tega, da se pred končnim stanjem delci gibljejo sem in tja (skačejo) v ciklu, je v algoritem pametno vključiti simulirano ohlajanje, ki z vsako iteracijo manjša sile, s katerimi delci delujejo drug na drugega. 
- V kolikor ne bo pretežko, enačbe algoritma predrugačimo tako, da bo delovalo v tridimenzionalnem prostoru, **vendar najprej implementiramo v dvodimenzionalnem prostoru**
- Korak pri izvajanju algoritma naj bo dolg (časovno), kolikor je velikost rezultante sil, ki delujejo na ta delec. Torej, ne simuliramo delvanje sil na časovno enoto, pač pa diskretno glede na seštevek sil v podanem koraku.

Za vse tri rešitve je predlagal, naj najprej implementiramo zaporedni program, tako da bomo problem razumeli in šele nato nadaljujem na vzporedne rešitve.  
Implementacija vseh treh rešitev naj omogoča, da bo uporabnik izvajal program s poljuno veliko (s parametri določeno) številom niti (**strojnih!**).  
Na STUDISU moram izpolniti obrazec za prijavo diplomske naloge, kjer označim mentorja in napišem (nekončen) naslov diplomske naloge. Ta naslov lahko spreminjava vse do prijave teme oziroma zagovora (tam nekje). Prijaviti moram do 15.4.2024. Opis naloge bo tudi spisal on: kakor sem razumel v angleščini in slovenščini - kakor vem je to tistij nekaj vrstic, ki se prikaže na spletni strani FRI-ja. Točnega naslova, ki ga je omenil se ne spomnim, nekaj v smislu: "Primerjava vzporedenja problemov v C, Julia in Golang." V bistvu niti približno tako, vem le, da je bilo o primerjavi in vzporedenju, nekaj tudi o jedrih.

17.07.2024; 09:00
---

- Kako naj primerjam jezike med seboj?
    
    Primejati moram konstrukte, podatkovne strukture ostalo orodje, tudi knjižnice, ki mi jih ponujajo jeziki (vse v obe smeri).

- Ali naj je narobe, če se algoritmi v različnih implementacijah razlikujejo?
    
    Ne, tako je tudi prav.

- Kakšen naj bi bil zaključek / ugotovitev diplomske naloge?

    Dobra ugotovitev za bralca bi bila na primer, da mu predlagam v kakšne namene je bolje uporabiti en ali drug jezik.

17.03.2025; 11:00
---

S profesorjem sva pogledala kaj sem naredil do sedaj - delovanje programja je zadovoljivo. Obdelala sva naslednje problematike: 
- Profesor je predlagal, da dodam možnost za izbiro števila niti, ki jih program uporabi. Odločil sem se, da bom to implementiral v `Makefile`. Namen tega je, da testiramo delovanje z uporabo števila niti, ki je enako številu jeder na procesorju.
- Pri merjenju časa je zaželjeno, da merim čas izvajanja algoritma po "stenski uri", saj tako dobimo najboljši rezultat časovnih meritev - kako jeziki (compiler-ji) in njihovi urniki obvladujejo vzporedne progame. 
    - Je zaradi vmesnih morebitnih prekinitev in preklapljanj med niti (kontekstov) in podobno takšno merejenje nezanesljivo?\
    Ne, saj se prekinitve in preklapljanja med niti dogajajo med merjenjem vseh algoritmov (vpliva na vse enako (v povprečju)), poleg tega pa bomo meritev naredili več, vzeli povprečje in tako v povprečju dobili zanesljive rezultate.
- Pri reševanju problemov imam veliko izbire za logično predstavitev problemov v vsakem jezikih (v kakšnih strukturah hranim podatke problemov). Odločili smo se, da bom podatke za posamezne probleme hranil v več dimenzionalnih poljih (arrayih).
    - Lahko zaradi tega pride do nepravičnih primerjav med jeziki, saj bi lahko kateri jezik uporabljal bolj optimalne strukture podatkov?\
    Do tega sicer lahko pride (težko), vendar so polja (arrayi) in matrike na področju superračunalnišva in vzporednega programiranja poglavitnega pomena in jih je smiselno uporabiti.
- Profesor bo priskrbel dotop do superračunalnika z velikim številom jeder, na katerem bom lahko zaganjal svoje programe
- Po zaganjanju vseh progrmaov lahko začnem že kar pisati diplomsko nalogo
- Ker seveda ne obstajajo metode, ki bi enolično pokazale, kateri jezik je boljši, bom moral uporabiti več metod primerjave in tako bralcu olajšati izbiro na podlagi le njegovih potreb. V delu bom primerjal:
    - numerično - primerjal bom čase izvajanja algoritmov na izbranih problemih
    - analitično (vsako rešitev) - vsakega jezika bom primerjal z rešitvami drugih jezikov

24.03.2025; 11:00
---

S profesorjem sva se sestala in tokrat posvetila več pozornosti Kamada Kawai algoritmu. Pogovor bom poskusil strniti v obliki vprašanj in odgovorov:
- Imel sem problem z omejujočimi `float` podatkovnimi tipi (posplošitev na 0 pri deljenju majhnih števil). Nadomestil sem jih z `double` podtakovnimi tipi. Naletel sem na problem osciliranja delcev. Kako lahko to rešim?
    - Algoritem bomo dopolnili na tri načine:
        - Kamada Kawai algoritem bomo dopolnili z metodo simuliranega ohlajanja: vpliv delte bomo po vsakem premiku zmanjševali tako, da bomo izračunane `delte` množili s faktorjem ohlajanja.
        - algoritem narekuje, naj po vsakem premiku (kakor to omejuje parameter epsilon) na novo izračunamo delte vseh ostalih delcev. Mi pa bomo poskusili ohraniti vrednost delt ostalih delcev in jih spremeniti le za spremebmo na novo premaknjenega delca.
        - eksperimentalno bomo poskusili premikati vse delce na grafu hkrati in poskusili ugotoviti, ali se tako algoritem lahko reši in ali je v katerih primerih (za specifično začetno postavitev delcev) tak pristop primernejši od izvornega algoirtma
- Zakaj je izbira `#niti=#nproc`  v primeru Kamada-Kawai algoritma primernejša od izbire `#niti=#nthreads`?
    - Procesorji večinoma (zaradi cene silicija) ponujajo eno floating point procesorsko enoto na procesorskem jedru. Ker se procesorski niti sinhronizirata/"borita" za floating point enoto, to proces operacij program upočasni.
- V katerem primeru je veliko število niti  (> od števila fizičnih niti) sploh uporabno?
    - Kadar vnparej vemo, da bodo nekater od naših niti blokirane, medtem, ko bodo druge imele možnost izvajanja - če bi večina ustvarjenih niti čakala na izvajanje, bi jih le malo izmed njih dobilo procesorski čas. Nasprotno pa lahko v primeru, da jih je ustvarjenih več, kot je procesorskih niti lahko nekaj čaka, a je vseeno med tem čakanjem veliki večini dodeljen procesorski čas
- Je Kamada Kawai algoritem zares odvisen od začentega položaja delcev?
    - Seveda.

31.03.2025; 11:00
---

Tokrat sva se s profesorjem osredotočila na performanco algoritmov. Skozi pogovor sva naredila nekaj zaključkov:
- Algoritme moram poganjati na dovolj velikem številu niti, zato, da vzporedenje sploh pride do izraza (sicer igra kreiranje in sinhroniziranje niti v programu večjo vlogo)
- Zakaj je ob uporabi polovice niti zasedenih vseh n niti
    - Menjajo se!

Plan:
- 1.) Nov sinhroni algoritem za Kamada-Kawai (premikanje n delcev)
- 2.) Ureditev golang in julia Kamada Kawai algoritma
- 3.) Priprava okolja za superračunalnik
- 4.) Analiza primerov: koliko delcev na nit (približno 100? zaenkrat)
- 5.) Kreiranje primernih testnih primerov
- 6.) Zagon testov na superračunalniku

22.04.2025; 09:00
---
Probleme morma zasnovati tako, da bom z vsakim problemom analiziral le en parameter (multithreading, nastavitve vzporedneja in tako dalje).\
Dodati je potrebno večkratno zaganjanje istega algoritma (za povprečenje).
