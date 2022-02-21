#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#define PAZYMYS_MIN 1
#define PAZYMYS_MAX 10

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;

struct Studentas
{
    string vardas;
    string pavarde;
    int pazymiuSk;
    int *pazymiai;
    int egzamino;
    double pazymiuVid;
    double pazymysGalutinis;
    double pazymiuMed;
};

void MasyvoKopijavimas(int *galutinisMasyvas, int *pradinisMasyvas, int dydis)
{
    for (int i = 0; i < dydis; i++)
    {
        galutinisMasyvas[i] = pradinisMasyvas[i];
    }
}

void MasyvoPushinimas(int *&masyvas, int &dydis, int value)
{
    int *laikinasMasyvas = new int[dydis + 1];
    MasyvoKopijavimas(laikinasMasyvas, masyvas, dydis);
    laikinasMasyvas[dydis] = value;

    delete[] masyvas;
    masyvas = laikinasMasyvas;
    dydis++;
}

void clearErrorFlagFunkcija()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool patvirtinti(const string &pranesimas, char taip = 'y', char ne = 'n')
{
    while (true)
    {
        cout << "-> " << pranesimas << " (" << taip << "/" << ne << "): ";

        char atsakas;
        cin >> atsakas;
        clearErrorFlagFunkcija();
        if (atsakas == taip)
        {
            return true;
        }
        else if (atsakas == ne)
        {
            return false;
        }
        else
        {
            cout << "Netinkamas simbolis ";
        }
    }
}

double VidurkioSkaiciavimas(int *masyvas, int ilgis)
{
    int sum = 0;
    for (int i = 0; i < ilgis; i++)
    {
        sum += masyvas[i];
    }

    return (double)sum / ilgis;
}

double MedianosPaieska(int *masyvas, int masyvoDydis)
{
    sort(masyvas, masyvas + masyvoDydis);

    bool ArVidurinis = masyvoDydis % 2 != 0;

    if (ArVidurinis)
    {
        return (double)masyvas[masyvoDydis / 2];
    }

    return (double)(masyvas[(masyvoDydis - 1) / 2] + masyvas[masyvoDydis / 2]) / 2.0;
}

void AtlaisvintiAtminti(Studentas *studentai, int studentuSk)
{
    for (int i = 0; i < studentuSk; i++)
    {
        delete[] studentai[i].pazymiai;
    }
    delete[] studentai;
}

int PazymiuSkaicius()
{
    cout << "Iveskite pazymiu skaiciu: ";
    int pazymiuSk;
    cin >> pazymiuSk;
    clearErrorFlagFunkcija();

    while (pazymiuSk < 0)
    {
        cout << "Pazymys negali buti neigiamas, iveskite nauja reiksme: ";
        cin >> pazymiuSk;
        clearErrorFlagFunkcija();
    }

    return pazymiuSk;
}

int GeneruotiAtsitiktiniIntervale(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

bool PazymioVerifikacija(int pazymys)
{
    return pazymys >= PAZYMYS_MIN && pazymys <= PAZYMYS_MAX;
}

void KuriSpausdinti(Studentas *studentas, bool RodytiVidurki = true)
{
    cout << left
         << setw(10) << studentas->vardas
         << setw(15) << studentas->pavarde
         << setw(12) << fixed << setprecision(2)
         << (RodytiVidurki ? studentas->pazymysGalutinis : studentas->pazymiuMed)
         << endl;
}

void Rezultatai(Studentas *studentai, int studentuSk, bool RodytiVidurki = true)
{
    cout << left
         << setw(10) << "Vardas"
         << setw(16) << "Pavarde"
         << "Galutinis " << (RodytiVidurki ? "Vid." : "Med.") << endl;
    cout << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < studentuSk; i++)
    {
        KuriSpausdinti(&studentai[i], RodytiVidurki);
    }
}

void printStudent(Studentas *studentas)
{
    cout << "Vardas: " << studentas->vardas << endl;
    cout << "Pavarde: " << studentas->pavarde << endl;
    cout << "Pazymiu skaicius: " << studentas->pazymiuSk << endl;

    cout << "Pazymiai: ";
    for (int i = 0; i < studentas->pazymiuSk; i++)
    {
        cout << studentas->pazymiai[i] << " ";
    }
    cout << endl;

    cout << "Egzamino pazymys: " << studentas->egzamino << endl;
    cout << "Pazymiu vidurkis: " << studentas->pazymiuVid << endl;
    cout << "Galutinis pazymys: " << studentas->pazymysGalutinis << endl;
    cout << "Pazymiu mediana: " << studentas->pazymiuMed << endl;
}

void StudentoFun(Studentas *studentas, bool ArSkaiciuotiVidurki = true)
{
    studentas->pazymysGalutinis = 0;
    studentas->pazymiuVid = 0;
    studentas->pazymiuMed = 0;
    if (ArSkaiciuotiVidurki)
    {
        if (studentas->pazymiuSk > 0)
        {
            studentas->pazymiuVid = VidurkioSkaiciavimas(studentas->pazymiai, studentas->pazymiuSk);
        }
        studentas->pazymysGalutinis = 0.4 * studentas->pazymiuVid + 0.6 * studentas->egzamino;
    }
    else
    {
        if (studentas->pazymiuSk > 0)
        {
            studentas->pazymiuMed = MedianosPaieska(studentas->pazymiai, studentas->pazymiuSk);
        }
    }
}

void SpausdintiAtsitiktiniusPazymius(Studentas *studentas)
{
    cout << "Sugeneruoti " << studentas->pazymiuSk << " sie atsitiktiniai pazymiai: ";
    for (int i = 0; i < studentas->pazymiuSk; i++)
    {
        cout << studentas->pazymiai[i] << " ";
    }
    cout << endl;
    cout << "Sugeneruotas atsitiktinis egzamino pazymys: " << studentas->egzamino << endl;
}

void StudentoPushinimas(Studentas *&studentai, int &studentuSk, Studentas studentas)
{
    Studentas *laikinasMasyvas = new Studentas[studentuSk + 1];

    for (int i = 0; i < studentuSk; i++)
    {
        laikinasMasyvas[i] = studentai[i];
    }

    laikinasMasyvas[studentuSk] = studentas;

    delete[] studentai;
    studentai = laikinasMasyvas;
    studentuSk++;
}

int main()
{
    int studentuSk = 0;
    Studentas *studentai = new Studentas[studentuSk];

    while (true)
    {
        Studentas studentas;

        cout << "Iveskite varda: ";
        getline(cin, studentas.vardas);

        cout << "Iveskite pavarde: ";
        getline(cin, studentas.pavarde);

        bool ArZinomasPazymiuSk = patvirtinti("Ar zinote tikslu pazymiu skaiciu?");
        studentas.pazymiuSk = ArZinomasPazymiuSk ? PazymiuSkaicius() : 0;
        studentas.pazymiai = new int[studentas.pazymiuSk];

        bool ArGeneruotiAtsitiktinius = false;
        if (studentas.pazymiuSk > 0)
        {
            ArGeneruotiAtsitiktinius = patvirtinti("Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)?");
        }

        if (ArGeneruotiAtsitiktinius)
        {
            if (ArZinomasPazymiuSk)
            {
                for (int i = 0; i < studentas.pazymiuSk; i++)
                {
                    studentas.pazymiai[i] = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
                }
            }
            else
            {
                while (true)
                {
                    int pazymys = GeneruotiAtsitiktiniIntervale(0, PAZYMYS_MAX);
                    if (PazymioVerifikacija(pazymys))
                    {
                        MasyvoPushinimas(studentas.pazymiai, studentas.pazymiuSk, pazymys);
                    }
                    else
                    {
                        break;
                    }
                }
            }
            studentas.egzamino = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
            SpausdintiAtsitiktiniusPazymius(&studentas);
        }
        else
        {
            if (ArZinomasPazymiuSk)
            {
                if (studentas.pazymiuSk > 0)
                {
                    cout << "Iveskite pazymius: ";
                    int PazymioIndeksas = 0;
                    while (PazymioIndeksas != studentas.pazymiuSk)
                    {
                        int pazymys;
                        cin >> pazymys;
                        if (!PazymioVerifikacija(pazymys))
                        {
                            cout << "Pazymys " << pazymys << " indeksu " << PazymioIndeksas << " neatitinka pazymiu intervalo ("
                                 << PAZYMYS_MIN << "-" << PAZYMYS_MAX << "). Istaisykite klaida bei pildykite pazymius toliau." << endl;
                            clearErrorFlagFunkcija();
                        }
                        else
                        {
                            studentas.pazymiai[PazymioIndeksas] = pazymys;
                            PazymioIndeksas++;
                        }
                    }

                    clearErrorFlagFunkcija();
                }
            }
            else
            {
                while (true)
                {
                    cout << "Iveskite pazymi [" << studentas.pazymiuSk << "] (iveskite -1, jei nenorite ivesti daugiau pazymiu): ";

                    int pazymys;
                    cin >> pazymys;
                    clearErrorFlagFunkcija();

                    if (pazymys == -1)
                    {
                        break;
                    }
                    else
                    {
                        if (!PazymioVerifikacija(pazymys))
                        {
                            cout << "Pazymys " << pazymys << " neatitinka pazymiu intervalo ("
                                 << PAZYMYS_MIN << "-" << PAZYMYS_MAX << ")." << endl;
                        }
                        else
                        {
                            MasyvoPushinimas(studentas.pazymiai, studentas.pazymiuSk, pazymys);
                        }
                    }
                }
            }

            cout << "Iveskite egzamino pazymi: ";
            cin >> studentas.egzamino;
            while (!PazymioVerifikacija(studentas.egzamino))
            {
                cout << "Pazymys " << studentas.egzamino << " neatitinka pazymiu intervalo ("
                     << PAZYMYS_MIN << "-" << PAZYMYS_MAX << "). Istaisykite klaida bei pildykite pazymius toliau." << endl;
                clearErrorFlagFunkcija();
                cin >> studentas.egzamino;
            }

            clearErrorFlagFunkcija();
        }

        StudentoPushinimas(studentai, studentuSk, studentas);
        if (!patvirtinti("Ar norite prideti studenta?"))
        {
            break;
        }
    }

    bool ArSkaiciuotiVidurki = patvirtinti("Ar skaiciuoti vidurki (kitu atveju bus skaiciuojama mediana)?");
    for (int i = 0; i < studentuSk; i++)
    {
        StudentoFun(&studentai[i], ArSkaiciuotiVidurki);
    }

    cout << endl;
    Rezultatai(studentai, studentuSk, ArSkaiciuotiVidurki);
    cout << endl;

    AtlaisvintiAtminti(studentai, studentuSk);

    return 0;
}