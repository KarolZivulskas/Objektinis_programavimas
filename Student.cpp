#include "Student.hpp"

double Student::GalutinioSkaiciavimas(double pazymiuVid, double egzamino) {
    return 0.4 * pazymiuVid + 0.6 * egzamino;
}

bool Student::ArNepasiseke(Studentas& student) {
    return student.pazymysGalutinis < 5;
}

void Student::SutvarkytiStudenta(Studentas* student, const string& rezTipas) {
    if (rezTipas == RESULT_TYPE_MEAN) {
        student->pazymiuVid = Math::VidurkioSkaiciavimas(student->pazymiai);
        student->pazymysGalutinis = GalutinioSkaiciavimas(student->pazymiuVid, student->egzamino);
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        student->pazymiuMed = Math::MedianosPaieska(student->pazymiai);
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        student->pazymiuVid = Math::VidurkioSkaiciavimas(student->pazymiai);
        student->pazymysGalutinis = GalutinioSkaiciavimas(student->pazymiuVid, student->egzamino);
        student->pazymiuMed = Math::MedianosPaieska(student->pazymiai);
    }
}