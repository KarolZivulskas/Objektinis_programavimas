#pragma once

#include <iostream>
#include <string>

namespace Table {
    struct Pavadinimai {
        std::string vardas = "Vardas";
        std::string pavarde = "Pavarde";
        std::string vidurkis = "Galutinis Vid.";
        std::string mediana = "Galutinis Med.";
        std::string namudarbai = "ND";
        std::string egzas = "Egz.";
    };

    struct Plotis {
        int vardas = 6 + 6;
        int pavarde = 7 + 9;
        int vidurkis = 14 + 1;
        int mediana = 14 + 1;
    };
}