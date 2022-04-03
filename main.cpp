// g++ -std=c++11 include/*.cpp 'main.cpp' -o 'main' && './main'

#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "Grades.hpp"
#include "Student.hpp"
#include "Students.hpp"
#include "Timer.hpp"

using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::string;
using std::vector;

string NustatytiRezTipa() {
    int prasytiRez = Console::prasytiInt("Pasirinkite, ka skaiciuosite: Vidurkis - (1), Mediana - (2), abu - (3):", 1, 3);

    string rezTipas = RESULT_TYPE_BOTH;
    if (prasytiRez == 1) {
        rezTipas = RESULT_TYPE_MEAN;
    }
    else if (prasytiRez == 2) {
        rezTipas = RESULT_TYPE_MEDIAN;
    }

    return rezTipas;
}

template <class A>
void DuomenuIvedimasRankiniuBudu(A& students) {
    while (true) {
        Student::Studentas student;
        student.vardas = Console::prasytiString("Iveskite varda: ");
        student.pavarde = Console::prasytiString("Iveskite pavarde: ");

        int pazymiuSk = 0;
        const bool ArZinomasPazymiuSk = Console::patvirtinti("Ar zinote pazymiu skaiciu?");
        if (ArZinomasPazymiuSk) {
            pazymiuSk = Console::prasytiInt("Iveskite pazymiu skaiciu", 0, 100);
        }

        bool ArGeneruotiAtsitiktiniusPazymius = false;
        if (!ArZinomasPazymiuSk || pazymiuSk > 0) {
            ArGeneruotiAtsitiktiniusPazymius = Console::patvirtinti("Ar generuoti pazymius atsitiktinai, kitu atveju bus prasoma ivesti rankiniu budu?");
        }

        if (ArGeneruotiAtsitiktiniusPazymius) {
            Grades::GeneruotiAtsitiktinai(ArZinomasPazymiuSk, pazymiuSk, student);
        }
        else {
            Grades::IvestiRankiniuBudu(ArZinomasPazymiuSk, pazymiuSk, student);
        }

        students.push_back(student);
        if (!Console::patvirtinti("Ar norite prideti dar viena studenta?")) {
            break;
        }
    }
}

void DuomenuIrasuGeneravimas() {
    vector<int> irasai = Console::prasytiIntu("Kiek irasu generuoti?", 1, 10000000);
    if (irasai.empty()) {
        return;
    }

    int irasuSk = irasai.size();
    cout << "Bus sukurti " << irasuSk << " " << ((irasuSk == 1) ? "failas" : "failai") << ": ";
    for (int i = 0; i < irasuSk; i++) {
        cout << irasai[i] << ".txt, ";
    }
    cout << endl;
    cout << std::fixed << std::setprecision(int(TIME_PRECISION));

    Timer timer;
    for (int i = 0; i < irasuSk; i++) {
        cout << "Kuriama \"" << irasai[i] << ".txt\":" << endl;
        timer.reset();
        Students::GeneruotiIrasus(irasai[i]);
        cout << "Is viso laiko: " << timer.elapsed() << endl;
        cout << "----------------------" << endl;
    }
}

void DuomenuIrasuFiltravimas() {
    string failoTipas = "txt";
    string aplankoVieta = DATA_FOLDER;
    vector<string> failuPavadinimai = File::PasirinktiFailusFoldery(aplankoVieta, failoTipas);
    if (failuPavadinimai.empty()) {
        return;
    }

    int FailuPavSk = failuPavadinimai.size();
    cout << "Bus apdorojama " << FailuPavSk << " " << ((FailuPavSk == 1) ? "failas" : "failai") << ": ";
    for (int i = 0; i < FailuPavSk; i++) {
        cout << failuPavadinimai[i] << ", ";
    }
    cout << endl;
    cout << std::fixed << std::setprecision(int(TIME_PRECISION));

    Timer timer;
    for (int i = 0; i < FailuPavSk; i++) {
        timer.reset();
        Students::Filtruoti(failuPavadinimai[i]);
        cout << "Is viso laiko: " << timer.elapsed() << endl;
        cout << "----------------------" << endl;
    }
}

template <class A>
void DuomenuNuskaitymasIsFailo(A& students) {
    string failoTipas = "txt";
    string aplankoVieta = DATA_FOLDER;
    string failoVieta = File::PasirinktiFailaFoldery(aplankoVieta, failoTipas);
    if (failoVieta.empty()) {
        const bool ArPerjungtiManualini = Console::patvirtinti(
            "Ar norite vietoje to suvesti pazymius ranka?");

        if (ArPerjungtiManualini) {
            cout << "Perjungiama i rankini rezima." << endl;
            DuomenuIvedimasRankiniuBudu(students);
        }
        else {
            cout << "Programa uzbaigiama." << endl;
        }
    }
    else {
        failoVieta = aplankoVieta + failoVieta;
        cout << "Duomenys nuskaitomi is failo \"" << failoVieta << "\"" << endl;
        Students::SkaitytiIsFailo(failoVieta, students);
    }
}

int main() {
    if (ARRAY_TYPE == TYPE_DEQUE) {
        cout << "using std::deque" << endl;
    }
    else if (ARRAY_TYPE == TYPE_LIST) {
        cout << "using std::list" << endl;
    }
    else if (ARRAY_TYPE == TYPE_VECTOR) {
        cout << "using std::vector" << endl;
    }

    cout << "1. Generuoti naujus irasus" << endl;
    cout << "2. Filtruoti irasus" << endl;
    cout << "3. Nuskaityti pazymius is failo" << endl;
    cout << "4. Ivesti pazymius ranka" << endl;
    int pasirinkimas = Console::prasytiInt("Pasirinkite:", 1, 4);

    try {
        if (pasirinkimas == 1) {
            DuomenuIrasuGeneravimas();
        }
        else if (pasirinkimas == 2) {
            DuomenuIrasuFiltravimas();
        }
        else {
#if ARRAY_TYPE == TYPE_DEQUE
            deque<Student::Studentas> students;
#elif ARRAY_TYPE == TYPE_LIST
            list<Student::Studentas> students;
#elif ARRAY_TYPE == TYPE_VECTOR
            vector<Student::Studentas> students;
#endif

            if (pasirinkimas == 3) {
                DuomenuNuskaitymasIsFailo(students);
            }
            else if (pasirinkimas == 4) {
                DuomenuIvedimasRankiniuBudu(students);
            }

            if (!students.empty()) {
                string rezTipas = NustatytiRezTipa();
                Students::SutvarkytiStudentus(students, rezTipas);
                Students::SpausdintiFormatuota(students, rezTipas);
            }
        }

        return 0;
    }
    catch (std::exception& error) {
        std::cerr << error.what() << endl;
    }
}