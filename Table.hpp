#pragma once

#include <algorithm>  // std::sort
#include <iomanip>    // std::fixed, left,setprecision, setw
#include <iostream>
#include <string>

#include "Definitions.hpp"
#include "Student.hpp"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;

namespace Table {
    struct Names {
        string vardas = "Vardas";
        string pavarde = "Pavarde";
        string vidurkis = "Galutinis Vid.";
        string median = "Galutinis Med.";
    };

    struct Width {
        int vardas = 6 + 6;
        int pavarde = 7 + 9;
        int vidurkis = 14 + 1;
        int median = 14 + 1;
    };

    void SpausdintiVienaRez(Student::Studentas*, const string&);
    void SpausdintiRezultatus(vector<Student::Studentas>&, const string&);
}