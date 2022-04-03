#include "Comparator.hpp"

bool Comparator::RikiuotiPagalGalutiniMazejant(const Student::Studentas& a, const Student::Studentas& b) {
    return a.pazymysGalutinis > b.pazymysGalutinis;
}

bool Comparator::RikiuotiPagalVardaDidejant(const Student::Studentas& a, const Student::Studentas& b) {
    return a.pavarde != b.pavarde
        ? a.pavarde < b.pavarde
        : a.vardas < b.vardas;
}