#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#define PAZYMYS_MIN 1
#define PAZYMYS_MAX 10
#define REZULTATAS_VIDURKIS "REZULTATAS_VIDURKIS"
#define REZULTATAS_MEDIANA "REZULTATAS_MEDIANA"
#define REZULTATAS_ABU "REZULTATAS_ABU"

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

struct Pavadinimai
{
  string vardas = "Vardas";
  string pavarde = "Pavarde";
  string vidurkis = "Galutinis Vid.";
  string median = "Galutinis Med.";
} pavadinimai;

struct Studentas
{
  string vardas;
  string pavarde;
  vector<int> pazymiai;
  int egzamino;
  double pazymiuVid;
  double pazymysGalutinis;
  double pazymiuMed;
};

struct Plotis
{
  int vardas = 6 + 6;
  int pavarde = 7 + 9;
  int vidurkis = 14 + 1;
  int median = 14 + 1;
} plotis;

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

bool ArEgzistuojaFailas(string failoVieta)
{
  ifstream failas(failoVieta);
  return failas.good();
}

double GalutinioSkaiciavimas(double pazymiuVid, double egzamino)
{
  return 0.4 * pazymiuVid + 0.6 * egzamino;
}

double VidurkioSkaiciavimas(vector<int> &masyvas)
{
  if (masyvas.empty())
  {
    return 0;
  }

  const int masyvoDydis = masyvas.size();
  int sum = 0;
  for (int i = 0; i < masyvoDydis; i++)
  {
    sum += masyvas[i];
  }

  return (double)sum / masyvoDydis;
}

double MedianosPaieska(vector<int> &masyvas)
{
  if (masyvas.empty())
  {
    return 0;
  }

  sort(masyvas.begin(), masyvas.end());

  const int masyvoDydis = masyvas.size();
  const bool ArVidurinis = masyvoDydis % 2 != 0;

  if (ArVidurinis)
  {
    return (double)masyvas[masyvoDydis / 2];
  }

  return (double)(masyvas[(masyvoDydis - 1) / 2] + masyvas[masyvoDydis / 2]) / 2.0;
}

int PazymiuSkaicius()
{
  cout << "Iveskite pazymiu skaiciu: ";
  int pazymiuSk;
  cin >> pazymiuSk;
  clearErrorFlagFunkcija();

  while (pazymiuSk < 0)
  {
    cout << "Pazymiu skaicius negali buti neigiamas, iveskite nauja reiksme: ";
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

void SpausdintiAtsitiktiniusPazymius(Studentas &studentas)
{
  cout << "Sugeneruoti " << studentas.pazymiai.size() << " sie atsitiktiniai pazymiai: ";
  for (int i = 0; i < studentas.pazymiai.size(); i++)
  {
    cout << studentas.pazymiai[i] << " ";
  }
  cout << endl;
  cout << "Sugeneruotas atsitiktinis egzamino pazymys: " << studentas.egzamino << endl;
}

void SpausdintiVienaRez(Studentas *studentas, const string &rezTipas, Plotis &plotis)
{
  cout << left
       << setw(plotis.vardas) << studentas->vardas
       << setw(plotis.pavarde) << studentas->pavarde
       << fixed << setprecision(2);

  if (rezTipas == REZULTATAS_VIDURKIS)
  {
    cout << setw(plotis.vidurkis) << studentas->pazymysGalutinis;
  }
  else if (rezTipas == REZULTATAS_MEDIANA)
  {
    cout << setw(plotis.median) << studentas->pazymiuMed;
  }
  else if (rezTipas == REZULTATAS_ABU)
  {
    cout << setw(plotis.vidurkis) << studentas->pazymysGalutinis;
    cout << setw(plotis.median) << studentas->pazymiuMed;
  }

  cout << endl;
}

void SpausdintiRezultatus(vector<Studentas> &studentai, const string &rezTipas)
{
  cout << left
       << setw(plotis.vardas) << pavadinimai.vardas
       << setw(plotis.pavarde) << pavadinimai.pavarde;

  int tableWidth = plotis.vardas + plotis.pavarde;

  if (rezTipas == REZULTATAS_VIDURKIS)
  {
    cout << setw(plotis.vidurkis) << pavadinimai.vidurkis;
    tableWidth += plotis.vidurkis;
  }
  else if (rezTipas == REZULTATAS_MEDIANA)
  {
    cout << setw(plotis.median) << pavadinimai.median;
    tableWidth += plotis.median;
  }
  else if (rezTipas == REZULTATAS_ABU)
  {
    cout << setw(plotis.vidurkis) << pavadinimai.vidurkis;
    tableWidth += plotis.vidurkis;
    cout << setw(plotis.median) << pavadinimai.median;
    tableWidth += plotis.median;
  }
  cout << endl;
  cout << string(tableWidth, '-') << endl;

  sort(studentai.begin(), studentai.end(),
       [](const Studentas &a, const Studentas &b)
       {
         return a.pavarde != b.pavarde
                    ? a.pavarde < b.pavarde
                    : a.vardas < b.vardas;
       });

  for (int i = 0; i < studentai.size(); i++)
  {
    SpausdintiVienaRez(&studentai[i], rezTipas, plotis);
  }
}

void SutvarkytiVienaStudenta(Studentas *studentas, const string &rezTipas)
{
  if (rezTipas == REZULTATAS_VIDURKIS)
  {
    studentas->pazymiuVid = VidurkioSkaiciavimas(studentas->pazymiai);
    studentas->pazymysGalutinis = GalutinioSkaiciavimas(studentas->pazymiuVid, studentas->egzamino);
  }
  else if (rezTipas == REZULTATAS_MEDIANA)
  {
    studentas->pazymiuMed = MedianosPaieska(studentas->pazymiai);
  }
  else if (rezTipas == REZULTATAS_ABU)
  {
    studentas->pazymiuVid = VidurkioSkaiciavimas(studentas->pazymiai);
    studentas->pazymysGalutinis = GalutinioSkaiciavimas(studentas->pazymiuVid, studentas->egzamino);
    studentas->pazymiuMed = MedianosPaieska(studentas->pazymiai);
  }
}

void SutvarkytiStudentus(vector<Studentas> &studentai, const string &rezTipas)
{
  for (int i = 0; i < studentai.size(); i++)
  {
    SutvarkytiVienaStudenta(&studentai[i], rezTipas);
  }
}

int PrasytiInt(string pranesimas, int min, int max)
{
  while (true)
  {
    cout << "-> " << pranesimas << " (" << min << "-" << max << "): ";

    int verte;
    cin >> verte;
    clearErrorFlagFunkcija();
    if (verte >= min && verte <= max)
    {
      return verte;
    }
    else
    {
      cout << "Verte neatitinka pazymiu intervalo ";
    }
  }
}

string PrasytiString(const string &pranesimas)
{
  string rezultatas;
  cout << "-> " << pranesimas;
  getline(cin, rezultatas);
  return rezultatas;
}

string NustatytiRezTipa()
{
  int PrasytiRez = PrasytiInt("Pasirinkite skaiciavimo buda: (1) - vidurkis, (2) - mediana, (3) - abu:", 1, 3);

  string rezTipas = REZULTATAS_ABU;
  if (PrasytiRez == 1)
  {
    rezTipas = REZULTATAS_VIDURKIS;
  }
  else if (PrasytiRez == 2)
  {
    rezTipas = REZULTATAS_MEDIANA;
  }

  return rezTipas;
}

bool ArSkaitytiIsFailo(const string &failoVieta)
{
  bool rezultatas = false;
  if (ArEgzistuojaFailas(failoVieta))
  {
    rezultatas = patvirtinti("(y) - skaityti is failo \"" + failoVieta + "\"; (n) - generuoti programoje arba ivesti ranka:");
  }
  else
  {
    cout << "Tokio failo nera \"" << failoVieta << "\". Vykdysime programa be isorinio failo." << endl;
  }

  return rezultatas;
}

void GeneruotiPazymiusRankiniuBudu(bool ArZinomasPazymiuSk, int pazymiuSk, Studentas &studentas)
{
  if (ArZinomasPazymiuSk)
  {
    if (pazymiuSk > 0)
    {
      cout << "Iveskite pazymius: ";
      while (studentas.pazymiai.size() != pazymiuSk)
      {
        int pazymys;
        cin >> pazymys;
        if (!PazymioVerifikacija(pazymys))
        {
          cout << "Pazymys " << pazymys << " indeksu " << studentas.pazymiai.size() << " neatitinka pazymiu intervalo ("
               << PAZYMYS_MIN << "-" << PAZYMYS_MAX << "). Istaisykite klaida bei pildykite pazymius toliau." << endl;
          clearErrorFlagFunkcija();
        }
        else
        {
          studentas.pazymiai.push_back(pazymys);
        }
      }

      clearErrorFlagFunkcija();
    }
  }
  else
  {
    while (true)
    {
      cout << "Iveskite pazymi [" << studentas.pazymiai.size() << "] (jei norite baigti, iveskite -1): ";

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
          studentas.pazymiai.push_back(pazymys);
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

void GeneruotiPazymiusAtsitiktinai(bool ArZinomasPazymiuSk, int pazymiuSk, Studentas &studentas)
{
  if (ArZinomasPazymiuSk)
  {
    for (int i = 0; i < pazymiuSk; i++)
    {
      int pazymys = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
      studentas.pazymiai.push_back(pazymys);
    }
  }
  else
  {
    while (true)
    {
      int pazymys = GeneruotiAtsitiktiniIntervale(0, PAZYMYS_MAX);
      if (PazymioVerifikacija(pazymys))
      {
        studentas.pazymiai.push_back(pazymys);
      }
      else
      {
        break;
      }
    }
  }
  studentas.egzamino = GeneruotiAtsitiktiniIntervale(PAZYMYS_MIN, PAZYMYS_MAX);
  SpausdintiAtsitiktiniusPazymius(studentas);
}

void SkaitytiPazymiusIsFailo(const string &failoVieta, vector<Studentas> &studentai)
{
  ifstream failas;
  failas.open(failoVieta);

  if (!failas)
  {
    cout << "Klaida - nepavyksta atverti failo" << endl;
    exit(1);
  }

  string eilute;
  getline(failas, eilute);
  while (getline(failas, eilute))
  {
    Studentas studentas;

    istringstream iss(eilute);
    iss >> studentas.vardas >> studentas.pavarde;

    int pazymys;
    while (iss >> pazymys)
    {
      studentas.pazymiai.push_back(pazymys);
    }

    studentas.pazymiai.pop_back();
    studentas.egzamino = pazymys;

    studentai.push_back(studentas);
  }

  failas.close();
}

int main()
{
  vector<Studentas> studentai;

  string failoVieta = "kursiokaiN.txt";
  if (ArSkaitytiIsFailo(failoVieta))
  {
    SkaitytiPazymiusIsFailo(failoVieta, studentai);
  }
  else
  {
    while (true)
    {
      Studentas studentas;
      studentas.vardas = PrasytiString("Iveskite varda: ");
      studentas.pavarde = PrasytiString("Iveskite pavarde: ");

      const bool ArZinomasPazymiuSk = patvirtinti("Ar zinote tikslu pazymiu skaiciu?");
      const int pazymiuSk = ArZinomasPazymiuSk ? PazymiuSkaicius() : 0;

      bool ArGeneruotiAtsitiktinius = false;
      if (!ArZinomasPazymiuSk || pazymiuSk > 0)
      {
        ArGeneruotiAtsitiktinius = patvirtinti("Ar generuoti pazymius atsitiktinai (jei ne, iveskite ranka)?");
      }

      if (ArGeneruotiAtsitiktinius)
      {
        GeneruotiPazymiusAtsitiktinai(ArZinomasPazymiuSk, pazymiuSk, studentas);
      }
      else
      {
        GeneruotiPazymiusRankiniuBudu(ArZinomasPazymiuSk, pazymiuSk, studentas);
      }

      studentai.push_back(studentas);
      if (!patvirtinti("Ar norite prideti studenta?"))
      {
        break;
      }
    }
  }

  string rezTipas = NustatytiRezTipa();
  SutvarkytiStudentus(studentai, rezTipas);

  cout << endl;
  SpausdintiRezultatus(studentai, rezTipas);
  cout << endl;

  return 0;
}