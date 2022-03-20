#include "Students.hpp"

void PridetiFormatuotaStudentaBuferiui(Student::Studentas* student, const string& rezTipas, stringstream& buffer) {
    struct Table::Plotis width;

    buffer << left
        << setw(width.vardas) << student->vardas
        << setw(width.pavarde) << student->pavarde
        << fixed << setprecision(2);

    if (rezTipas == RESULT_TYPE_MEAN) {
        buffer << setw(width.vidurkis) << student->pazymysGalutinis;
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        buffer << setw(width.mediana) << student->pazymiuMed;
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        buffer << setw(width.vidurkis) << student->pazymysGalutinis;
        buffer << setw(width.mediana) << student->pazymiuMed;
    }

    buffer << "\n";
}

void PridetiFormatuotaAntrasteBuferiui(stringstream& buffer, const string& rezTipas) {
    struct Table::Plotis width;
    struct Table::Pavadinimai names;

    buffer << left
        << setw(width.vardas) << names.vardas
        << setw(width.pavarde) << names.pavarde;

    int lentelesPlotis = width.vardas + width.pavarde;

    if (rezTipas == RESULT_TYPE_MEAN) {
        buffer << setw(width.vidurkis) << names.vidurkis;
        lentelesPlotis += width.vidurkis;
    }
    else if (rezTipas == RESULT_TYPE_MEDIAN) {
        buffer << setw(width.mediana) << names.mediana;
        lentelesPlotis += width.mediana;
    }
    else if (rezTipas == RESULT_TYPE_BOTH) {
        buffer << setw(width.vidurkis) << names.vidurkis;
        lentelesPlotis += width.vidurkis;
        buffer << setw(width.mediana) << names.mediana;
        lentelesPlotis += width.mediana;
    }

    buffer << "\n";
    buffer << string(lentelesPlotis, '-') << "\n";
}

void PridetiAntrasteIBuferi(stringstream& buffer, int pazymiuSk) {
    const struct Table::Pavadinimai names;
    const struct Table::Plotis width;

    const int pazymioPlotis = names.namudarbai.size() + Utils::RastiSkaitmenuSkaiciu(pazymiuSk) + 1;
    buffer << left
        << setw(width.vardas) << names.vardas
        << setw(width.pavarde) << names.pavarde;

    for (int i = 1; i <= pazymiuSk; i++) {
        buffer << setw(pazymioPlotis) << names.namudarbai + std::to_string(i);
    }

    buffer << names.egzas << "\n";
}

void PridetiStudentaIBuferi(Student::Studentas& student, stringstream& buffer) {
    const struct Table::Plotis width;

    buffer << setw(width.vardas) << student.vardas
        << setw(width.pavarde) << student.pavarde;

    for (int i = 0, il = student.pazymiai.size(); i < il; i++) {
        buffer << setw(5) << student.pazymiai[i];
    }

    buffer << student.egzamino << "\n";
}

void PridetiAtsitiktiniusStudentusIBuferi(stringstream& buffer, int studentuSkaic, int pazymiuSk) {
    const struct Table::Pavadinimai names;
    const struct Table::Plotis width;

    for (int i = 1; i <= studentuSkaic; i++) {
        buffer << setw(width.vardas) << names.vardas + std::to_string(i)
            << setw(width.pavarde) << names.pavarde + std::to_string(i);

        for (int j = 1; j <= pazymiuSk; j++) {
            buffer << setw(5) << RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX);
        }

        buffer << RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX) << "\n";
    }
}

void Students::Filtruoti(const string& failoPavadinimas) {
    Timer timer;
    string aplankoVieta = DATA_FOLDER;
    string failoVieta = aplankoVieta + failoPavadinimas;
    vector<Student::Studentas> students;

    timer.reset();
    cout << "Nuskaitoma informacija is \"" << failoPavadinimas << "\"..." << endl;
    SkaitytiIsFailo(failoVieta, students);
    cout << "Nuskaitoma informacija is \"" << failoPavadinimas << "\"..." << timer.elapsed() << endl;

    if (students.empty()) {
        throw std::runtime_error("Klaida: faile \"" + failoVieta + "\" nera informacijos apie studentus");
    }

    string rezTipas = RESULT_TYPE_MEAN;
    cout << "Apdoroja studentu informacija...";
    timer.reset();
    Students::SutvarkytiStudentus(students, rezTipas);
    cout << timer.elapsed() << endl;

    cout << "Rikiuoja studentus pagal galutini pazymi mazejancia tvarka...";
    timer.reset();
    Students::RikiuotiPagalGalutiniMazejant(students);
    cout << timer.elapsed() << endl;

    cout << "Ieskoma pirmojo nesekmingo studento...";
    timer.reset();
    auto it = std::find_if(
        students.begin(), students.end(), Student::ArNepasiseke);
    cout << timer.elapsed() << endl;

    cout << "Visi, kuriems nepasiseke, kopijuojami i kita vektoriu...";
    timer.reset();
    vector<Student::Studentas> Nesekmingi(students.end() - it);
    std::copy(it, students.end(), Nesekmingi.begin());
    cout << timer.elapsed() << endl;

    cout << "Keiciamas pirminio vektoriaus dydis...";
    timer.reset();
    students.resize(it - students.begin());
    cout << timer.elapsed() << endl;

    string baseName = File::getBaseName(failoPavadinimas);
    if (Nesekmingi.empty()) {
        cout << "Klaseje nera nesekminguju" << endl;
    }
    else {
        cout << "Nesekmingieji irasomi i faila..." << endl;
        timer.reset();
        Students::Issaugoti(Nesekmingi, aplankoVieta + baseName + " Nesekmingi.txt");
        cout << "Nesekmingieji irasomi i faila..." << timer.elapsed() << endl;
    }

    if (students.empty()) {
        cout << "Klaseje nera sekminguju" << endl;
    }
    else {
        cout << "Sekmingieji irasomi i faila..." << endl;
        timer.reset();
        Students::Issaugoti(students, aplankoVieta + baseName + " Sekmingi.txt");
        cout << "Sekmingieji irasomi i faila..." << timer.elapsed() << endl;
    }
}

void Students::GeneruotiIrasus(int studentuSkaic) {
    Timer timer;
    const int pazymiuSk = 10;
    std::stringstream buffer;

    cout << "Buferinami studentai...";
    timer.reset();
    PridetiAntrasteIBuferi(buffer, pazymiuSk);
    PridetiAtsitiktiniusStudentusIBuferi(buffer, studentuSkaic, pazymiuSk);
    cout << timer.elapsed() << endl;

    const string failoVieta = string(DATA_FOLDER) + "Atsitiktinis " + std::to_string(studentuSkaic) + ".txt";
    cout << "Buferis issaugojamas...";
    timer.reset();
    File::IssaugotiBuferi(failoVieta, buffer);
    cout << timer.elapsed() << endl;
}

void Students::SpausdintiFormatuota(vector<Student::Studentas>& students, const string& rezTipas) {
    stringstream buffer;
    PridetiFormatuotaAntrasteBuferiui(buffer, rezTipas);

    cout << "Studentai rikiuojami pagal varda..." << endl;
    RikiuotiPagalVardaDidejant(students);

    cout << "Buferinami studentai..." << endl;
    for (int i = 0, il = students.size(); i < il; i++) {
        PridetiFormatuotaStudentaBuferiui(&students[i], rezTipas, buffer);
    }

    bool ArIssaugotiFaila = Console::patvirtinti("Parasykite y, jei norite saugoti i faila, n, jei norite rezultata matyti konsoleje:");

    if (ArIssaugotiFaila) {
        string failoVieta = string(DATA_FOLDER) + "Formatuotas.txt";
        cout << "Saugomas failas..." << endl;
        File::IssaugotiBuferi(failoVieta, buffer);
        cout << "Failas issaugotas" << endl;
    }
    else {
        cout << buffer.str() << endl;
    }
}

void Students::SutvarkytiStudentus(vector<Student::Studentas>& students, const string& rezTipas) {
    for (int i = 0, il = students.size(); i < il; i++) {
        Student::SutvarkytiStudenta(&students[i], rezTipas);
    }
}

void Students::SkaitytiIsFailo(const string& failoVieta, vector<Student::Studentas>& students) {
    Timer timer;
    timer.start();

    cout << "Buferinamas failas...";
    stringstream buffer = File::GrazintiBuferi(failoVieta);
    cout << timer.elapsed() << endl;

    timer.reset();
    cout << "Apdorojamas buferis...";
    string eilute;
    getline(buffer, eilute);
    while (getline(buffer, eilute)) {
        Student::Studentas student;

        stringstream iss(eilute);
        iss >> student.vardas >> student.pavarde;

        int pazymys;
        while (iss >> pazymys) {
            student.pazymiai.push_back(pazymys);
        }

        student.pazymiai.pop_back();
        student.egzamino = pazymys;

        students.push_back(student);
    }

    cout << timer.elapsed() << endl;
}

void Students::Issaugoti(vector<Student::Studentas>& students, const string& failoVieta) {
    stringstream buffer;
    const int pazymiuSk = students[0].pazymiai.size();

    Timer timer;
    cout << "Buferinami studentai...";
    timer.reset();
    PridetiAntrasteIBuferi(buffer, pazymiuSk);
    for (int i = 0, il = students.size(); i < il; i++) {
        PridetiStudentaIBuferi(students[i], buffer);
    }
    cout << timer.elapsed() << endl;

    timer.reset();
    cout << "Buferis irasomas i faila...";
    File::IssaugotiBuferi(failoVieta, buffer);
    cout << timer.elapsed() << endl;
}

void Students::RikiuotiPagalGalutiniMazejant(vector<Student::Studentas>& students) {
    sort(students.begin(), students.end(),
        [](const Student::Studentas& a, const Student::Studentas& b) {
            return a.pazymysGalutinis > b.pazymysGalutinis;
        });
}

void Students::RikiuotiPagalVardaDidejant(vector<Student::Studentas>& students) {
    sort(students.begin(), students.end(),
        [](const Student::Studentas& a, const Student::Studentas& b) {
            return a.pavarde != b.pavarde
                ? a.pavarde < b.pavarde
                : a.vardas < b.vardas;
        });
}