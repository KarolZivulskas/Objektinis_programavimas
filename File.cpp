#include "File.hpp"
#include <algorithm>

bool File::ArEgzistuojaFailas(const string& failoVieta) {
    struct stat info;
    return stat(failoVieta.c_str(), &info) == 0;
}

stringstream File::GrazintiBuferi(const string& failoVieta) {
    ifstream failas;
    failas.open(failoVieta);

    if (!failas) {
        throw std::runtime_error("Klaida: failas \"" + failoVieta + "\" negali buti atidarytas");
    }

    stringstream buffer;
    buffer << failas.rdbuf();
    failas.close();

    return buffer;
}

vector<string> File::FailuPavadinimai(const string& aplankoVieta, const string& failoTipas) {
    DIR* direktorija = opendir(aplankoVieta.c_str());
    struct dirent* pradzia;
    vector<string> failuPavadinimai;

    if (direktorija != NULL) {
        while ((pradzia = readdir(direktorija)) != NULL) {
            string failoPavadinimas = pradzia->d_name;
            if (String::ArTuriPriesaga(failoPavadinimas, failoTipas)) {
                failuPavadinimai.push_back(failoPavadinimas);
            }
        }
        closedir(direktorija);
    }

    return failuPavadinimai;
}

bool File::ArYraFailas(const string& failoVieta) {
    struct stat info;
    if (stat(failoVieta.c_str(), &info) == 0) {
        if (info.st_mode & S_IFREG) {
            return true;
        }
    }
    return false;
}

bool File::ArYraAplankas(const string& failoVieta) {
    struct stat info;
    if (stat(failoVieta.c_str(), &info) == 0) {
        if (info.st_mode & S_IFDIR) {
            return true;
        }
    }
    return false;
}

string File::PasirinktiFailaAplanke(const string& aplankoVieta, const string& failoTipas) {
    string failoPavadinimas;
    if (!ArEgzistuojaFailas(aplankoVieta)) {
        cout << "Aplankas \"" << aplankoVieta << "\" neegzistuoja." << endl;
    }
    else if (!ArYraAplankas(aplankoVieta)) {
        cout << "\"" << aplankoVieta << "\" nera aplankas." << endl;
    }
    else {
        vector<string> failuPavadinimai = FailuPavadinimai(aplankoVieta, failoTipas);
        int failuSkaicius = failuPavadinimai.size();
        if (failuSkaicius == 0) {
            cout << "Aplankas \"" << aplankoVieta << "\" neturi failu su tokia pabaiga \"" << failoTipas << "\"." << endl;
        }
        else if (failuSkaicius == 1) {
            failoPavadinimas = failuPavadinimai[0];
        }
        else {
            std::sort(failuPavadinimai.begin(), failuPavadinimai.end());

            cout << "Aplankas \"" << aplankoVieta << "\" turi keleta failu. Pasirinkite viena:" << endl;
            for (int i = 0; i < failuSkaicius; i++) {
                cout << i + 1 << ": " << failuPavadinimai[i] << endl;
            }

            int indeksas = Console::PrasytiInt("Pasirinkite skaiciu:", 1, failuSkaicius);
            failoPavadinimas = failuPavadinimai[indeksas - 1];
        }
    }

    return failoPavadinimas;
}
