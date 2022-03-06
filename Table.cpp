#include "Table.hpp"

void Table::SpausdintiVienaRez(Student::Studentas* studentas, const string& rezTipas) {
    struct Width width;
    cout << left
        << setw(width.vardas) << studentas->vardas
        << setw(width.pavarde) << studentas->pavarde
        << fixed << setprecision(2);

    if (rezTipas == RESULT_TYPE_MEAN) {
        cout << setw(width.vidurkis) << studentas->pazymysGalutinis;
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        cout << setw(width.median) << studentas->pazymiuMed;
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        cout << setw(width.vidurkis) << studentas->pazymysGalutinis;
        cout << setw(width.median) << studentas->pazymiuMed;
    }

    cout << endl;
}

void Table::SpausdintiRezultatus(vector<Student::Studentas>& studentai, const string& rezTipas) {
    struct Width width;
    struct Names names;

    cout << left
        << setw(width.vardas) << names.vardas
        << setw(width.pavarde) << names.pavarde;

    int tableWidth = width.vardas + width.pavarde;

    if (rezTipas == RESULT_TYPE_MEAN) {
        cout << setw(width.vidurkis) << names.vidurkis;
        tableWidth += width.vidurkis;
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        cout << setw(width.median) << names.median;
        tableWidth += width.median;
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        cout << setw(width.vidurkis) << names.vidurkis;
        tableWidth += width.vidurkis;
        cout << setw(width.median) << names.median;
        tableWidth += width.median;
    }
    cout << endl;
    cout << string(tableWidth, '-') << endl;

    sort(studentai.begin(), studentai.end(),
        [](const Student::Studentas& a, const Student::Studentas& b) {
            return a.pavarde != b.pavarde
                ? a.pavarde < b.pavarde
                : a.vardas < b.vardas;
        });

    for (int i = 0, il = studentai.size(); i < il; i++) {
        SpausdintiVienaRez(&studentai[i], rezTipas);
    }
}
