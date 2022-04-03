# Objektinis_programavimas_1užduotis
Šioje repozitorijoje pateikiamos VU Objektinio programavimo kurso pirmos praktinės užduoties 0.4 V versija.

# Funkcionalumas
Programa leidžia suvesti arba atsitiktinai generuoti norimo studentų skaičiaus namų darbų rezultatus, egzamino rezultatą. Galima pasirinkti, kiek namų darbų atliko studentas. Taip pat galima pasirinkti ar galutinis rezultatas skaičiuojamas kaip vidurkis ar yra rodoma pažymių mediana. Programos patobulinimas leidžia generuoti įrašų failus automatiškai, juos leidžia išskaidyti, rikiuoti bei nuskaityti į naują failą.

## Vartotojo įvestis
Komandinėje eilutėje prašoma įvesti pasirinkimo skaičius, pagal kuriuos vykdomi scenarijai.


# Programos veikimas praktikoje

## Naujų įrašų generavimas


```shell
1. Generuoti naujus irasus
2. Filtruoti irasus
3. Nuskaityti pazymius is failo
4. Ivesti pazymius ranka
-> Pasirinkite: (1-4): 1
-> Kiek irasu generuoti? (1-10000000): 100000
Bus sukurti 1 failas: 100000.txt,
Kuriama "100000.txt":
Buferinami studentai...6.20578
Buferis issaugojamas...0.06061
Is viso laiko: 6.27224
----------------------
```

## Įrašų filtravimas


```shell
1. Generuoti naujus irasus
2. Filtruoti irasus
3. Nuskaityti pazymius is failo
4. Ivesti pazymius ranka
-> Pasirinkite: (1-4): 2
Bus apdorojama 1 failas: Atsitiktinis 100000.txt,
Nuskaitoma informacija is "Atsitiktinis 100000.txt"...
Buferinamas failas...0.56980
Apdorojamas buferis...10.22099
Nuskaitoma informacija is "Atsitiktinis 100000.txt"...10.79604
Apdoroja studentu informacija...0.04304
Rikiuoja studentus pagal galutini pazymi mazejancia tvarka...2.59348
Ieskoma pirmojo nesekmingo studento...0.00223
Visi, kuriems nepasiseke, kopijuojami i kita vektoriu...0.25391
Keiciamas pirminio vektoriaus dydis...0.11314
Nesekmingieji irasomi i faila...
Buferinami studentai...2.10506
Buferis irasomas i faila...0.03366
Nesekmingieji irasomi i faila...2.14230
Sekmingieji irasomi i faila...
Buferinami studentai...2.98760
Buferis irasomas i faila...0.03931
Sekmingieji irasomi i faila...3.03000
Is viso laiko: 19.17090
----------------------
```

## Filtruotų įrašų nuskaitymas

```shell
1. Generuoti naujus irasus
2. Filtruoti irasus
3. Nuskaityti pazymius is failo
4. Ivesti pazymius ranka
-> Pasirinkite: (1-4): 3
Aplanke "./data/" yra keletas failu. Pasirinkite viena:
1: Atsitiktinis 100000 Nesekmingi.txt
2: Atsitiktinis 100000 Sekmingi.txt
3: Atsitiktinis 100000.txt
-> Pasirinkite faila: (1-3): 2
Duomenys nuskaitomi is failo "./data/Atsitiktinis 100000 Sekmingi.txt"
Buferinamas failas...0.323131
Apdorojamas buferis...5.51407
-> Pasirinkite, ka skaiciuosite: Vidurkis - (1), Mediana - (2), abu - (3): (1-3): 1
Studentai rikiuojami pagal varda...
Buferinami studentai...
-> Parasykite y, jei norite saugoti i faila, n, jei norite rezultata matyti konsoleje: (y/n): y
Saugomas failas...
Failas issaugotas
```

# Įgyvendinimas
Ši pirminė versija yra įgyvendinta praeitų versijų kodo pagrindu.

# Patobulinimas
Ši programos versija gali veikti tiek su vector, tiek list bei deque. Programa veikia taip pat kaip ir V0.4, tik parodo kuriam iš trijų (vector, list ar deque) veikia.
