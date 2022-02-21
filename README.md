# Objektinis_programavimas_1užduotis
Šioje repozitorijoje pateikiamos VU Objektinio programavimo kurso pirmos praktinės užduoties versijos.

# Funkcionalumas
Programa leidžia suvesti arba atsitiktinai generuoti norimo studentų skaičiaus namų darbų rezultatus, egzamino rezultatą. Galima pasirinkti, kiek namų darbų atliko studentas. Taip pat galima pasirinkti ar galutinis rezultatas skaičiuojamas kaip vidurkis ar yra rodoma pažymių mediana.

## Vartotojo įvestis
Komandinėje eilutėje prašoma įvesti šiuos duomenis programos vykdymo laikotarpyje:
1) Studento vardas;
2) Studento pavardė;
3) Namų darbų skaičius;
4) Namų darbų įvertinimai;
5) Pasirinkimo (yes/no) atsakymai (pvz., klausimams apie medianą ir vidurkį).

# Programos veikimas praktikoje

## Atvejis be klaidos
Šiame atvejyje duomenys įvedami teisingai, tad programa atlieka viską sklandžiai bei neragina naudotojo taisyti klaidas:

```shell
Iveskite varda: Karolis
Iveskite pavarde: Zivulskas
-> Ar zinote tikslu pazymiu skaiciu? (y/n): y
Iveskite pazymiu skaiciu: 4
-> Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)? (y/n): y
Sugeneruoti 4 sie atsitiktiniai pazymiai: 3 4 9 6 
Sugeneruotas atsitiktinis egzamino pazymys: 1     
-> Ar norite prideti studenta? (y/n): n
-> Ar skaiciuoti vidurki (kitu atveju bus skaiciuojama mediana)? (y/n): y

Vardas    Pavarde        Galutinis Vid.
-----------------------------------------------------------
Karolis   Zivulskas      2.80
```

## Atvejis su klaida
Šiame atvejyje pažymys yra įvedamas kaip '76'. Kadangi toks skaičius yra už pažymių ribos (1-10), programa prašo ištaisyti klaidą bei pildyti kitus pažymius:

```shell
Iveskite varda: Karolis
Iveskite pavarde: Zivulskas
-> Ar zinote tikslu pazymiu skaiciu? (y/n): y
Iveskite pazymiu skaiciu: 4
-> Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)? (y/n): y
Sugeneruoti 4 sie atsitiktiniai pazymiai: 9 4 10 1 
Sugeneruotas atsitiktinis egzamino pazymys: 10
-> Ar norite prideti studenta? (y/n): y
Iveskite varda: Vardas
Iveskite pavarde: Pavardas
-> Ar zinote tikslu pazymiu skaiciu? (y/n): y
Iveskite pazymiu skaiciu: 3
-> Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)? (y/n): n
Iveskite pazymius: 3
76
Pazymys 76 indeksu 1 neatitinka pazymiu intervalo (1-10). Istaisykite klaida bei pildykite pazymius toliau.
4
6
Iveskite egzamino pazymi: 3
-> Ar norite prideti studenta? (y/n): n
-> Ar skaiciuoti vidurki (kitu atveju bus skaiciuojama mediana)? (y/n): y

Vardas    Pavarde         Galutinis Vid.
-----------------------------------------------------------
Karolis   Zivulskas      8.40
Vardas    Pavardas       3.53
```

# Įgyvendinimas
Ši pirminė versija yra įgyvendinta tiek standartinio masyvo, tiek vektorių pagrindu, kaip siūlyta užduotyje.
