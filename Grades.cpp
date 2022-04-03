#include "Grades.hpp"

void SpausdintiAtsitiktiniusPazymius(Student::Studentas& student) {
    const int masyvoDydis = student.pazymiai.size();
    std::cout << "Sugeneruoti " << masyvoDydis << " atsitiktiniai pazymiai: ";
    for (const int& pazymys : student.pazymiai) {
        std::cout << pazymys << " ";
    }
    std::cout << std::endl;
    std::cout << "Sugeneruotas atsitiktinis egzamino pazymys: " << student.egzamino << std::endl;
}

void Grades::IvestiRankiniuBudu(bool ArZinomasPazymiuSk, int pazymiuSk, Student::Studentas& student) {
    if (ArZinomasPazymiuSk) {
        if (pazymiuSk > 0) {
            while (student.pazymiai.size() != pazymiuSk) {
                int pazymys = Console::prasytiInt("Iveskite pazymi", GRADE_MIN, GRADE_MAX);
                student.pazymiai.push_back(pazymys);
            }
        }
    }
    else {
        while (true) {
            int pazymys = Console::prasytiInt(
                "Iveskite pazymi, jei norite sustoti, veskite -1", GRADE_MIN, GRADE_MAX, -1);
            if (pazymys == -1) {
                break;
            }
            else {
                student.pazymiai.push_back(pazymys);
            }
        }
    }

    student.egzamino = Console::prasytiInt("Iveskite egzamino pazymi", GRADE_MIN, GRADE_MAX);
}

void Grades::GeneruotiAtsitiktinai(bool ArZinomasPazymiuSk, int pazymiuSk, Student::Studentas& student) {
    if (ArZinomasPazymiuSk) {
        for (int i = 0; i < pazymiuSk; i++) {
            int pazymys = RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX);
            student.pazymiai.push_back(pazymys);
        }
    }
    else {
        while (true) {
            int pazymys = RND::GeneruotiAtsitiktiniIntervale(0, GRADE_MAX);
            if (pazymys == 0) {
                break;
            }
            else {
                student.pazymiai.push_back(pazymys);
            }
        }
    }
    student.egzamino = RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX);
    SpausdintiAtsitiktiniusPazymius(student);
}
