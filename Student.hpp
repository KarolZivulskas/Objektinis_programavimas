#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Definitions.hpp"
#include "Math.hpp"

using std::string;
using std::vector;

namespace Student {

    struct Studentas {
        string vardas;
        string pavarde;
        vector<int> pazymiai;
        int egzamino;
        double pazymiuVid;
        double pazymysGalutinis;
        double pazymiuMed;
    };

    double GalutinioSkaiciavimas(double, double);
    void SutvarkytiVienaStudenta(Studentas*, const string&);
    void SutvarkytiStudentus(vector<Studentas>&, const string&);
}