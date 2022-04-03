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
    bool ArNepasiseke(Studentas&);
    void SutvarkytiStudenta(Studentas*, const string&);
}
