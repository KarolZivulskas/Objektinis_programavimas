#include "Student.hpp"

double Student::GalutinioSkaiciavimas(double pazymiuVid, double egzamino) {
    return 0.4 * pazymiuVid + 0.6 * egzamino;
}

void Student::SutvarkytiVienaStudenta(Studentas* studentas, const string& rezTipas) {
    if (rezTipas == RESULT_TYPE_MEAN) {
        studentas->pazymiuVid = Math::VidurkioSkaiciavimas(studentas->pazymiai);
        studentas->pazymysGalutinis = GalutinioSkaiciavimas(studentas->pazymiuVid, studentas->egzamino);
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        studentas->pazymiuMed = Math::MedianosPaieska(studentas->pazymiai);
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        studentas->pazymiuVid = Math::VidurkioSkaiciavimas(studentas->pazymiai);
        studentas->pazymysGalutinis = GalutinioSkaiciavimas(studentas->pazymiuVid, studentas->egzamino);
        studentas->pazymiuMed = Math::MedianosPaieska(studentas->pazymiai);
    }
}

void Student::SutvarkytiStudentus(vector<Studentas>& studentai, const string& rezTipas) {
    for (int i = 0, il = studentai.size(); i < il; i++) {
        SutvarkytiVienaStudenta(&studentai[i], rezTipas);
    }
}
