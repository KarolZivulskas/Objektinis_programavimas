#include "File.hpp"

void SpausdintiFailuPavadinimus(vector<string>& failuPavadinimai) {
    for (int i = 0, il = failuPavadinimai.size(); i < il; i++) {
        std::cout << i + 1 << ": " << failuPavadinimai[i] << std::endl;
    }
}

bool File::ArEgzistuojaFailas(const string& failoVieta) {
    struct stat info {};
    return stat(failoVieta.c_str(), &info) == 0;
}

string File::getBaseName(const string& failoPavadinimas) {
    size_t lastIndex = failoPavadinimas.find_last_of('.');
    string baseName = failoPavadinimas.substr(0, lastIndex);
    return baseName;
}

stringstream File::GrazintiBuferi(const string& failoVieta) {
    std::ifstream file;
    file.open(failoVieta);

    if (!file) {
        throw std::runtime_error("Klaida: failas \"" + failoVieta + "\" negali buti atidarytas");
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer;
}

vector<string> File::FailuPavadinimaiAplanke(const string& aplankoVieta, const string& failoTipas) {
    DIR* directory = opendir(aplankoVieta.c_str());
    struct dirent* entry;
    vector<string> failuPavadinimai;

    if (directory != nullptr) {
        while ((entry = readdir(directory)) != nullptr) {
            string failoPavadinimas = entry->d_name;
            if (String::ArTuriPriesaga(failoPavadinimas, failoTipas)) {
                failuPavadinimai.push_back(failoPavadinimas);
            }
        }
        closedir(directory);
    }

    return failuPavadinimai;
}

[[maybe_unused]] bool File::ArYraFailas(const string& failoVieta) {
    struct stat info {};
    if (stat(failoVieta.c_str(), &info) == 0) {
        if (info.st_mode & S_IFREG) {
            return true;
        }
    }
    return false;
}

bool File::ArYraAplankas(const string& failoVieta) {
    struct stat info {};
    if (stat(failoVieta.c_str(), &info) == 0) {
        if (info.st_mode & S_IFDIR) {
            return true;
        }
    }
    return false;
}

void File::IssaugotiBuferi(const string& failoVieta, stringstream& buffer) {
    std::ofstream file;
    file.open(failoVieta);

    if (!file) {
        throw std::runtime_error("Klaida: failas \"" + failoVieta + "\" negali buti atidarytas");
    }

    file << buffer.str();
    file.close();
}

string File::PasirinktiFailaFoldery(const string& aplankoVieta, const string& failoTipas) {
    string failoPavadinimas;
    if (!ArEgzistuojaFailas(aplankoVieta)) {
        std::cout << "Aplankas \"" << aplankoVieta << "\" neegzistuoja." << std::endl;
    }
    else if (!ArYraAplankas(aplankoVieta)) {
        std::cout << "\"" << aplankoVieta << "\" nera aplankas." << std::endl;
    }
    else {
        vector<string> failuPavadinimai = FailuPavadinimaiAplanke(aplankoVieta, failoTipas);
        int failuSkaicius = failuPavadinimai.size();
        if (failuSkaicius == 0) {
            std::cout << "Aplankas \"" << aplankoVieta << "\" nera failu su tokia pabaiga \"" << failoTipas << "\"." << std::endl;
        }
        else if (failuSkaicius == 1) {
            failoPavadinimas = failuPavadinimai[0];
        }
        else {
            std::sort(failuPavadinimai.begin(), failuPavadinimai.end());

            std::cout << "Aplanke \"" << aplankoVieta << "\" yra keletas failu. Pasirinkite viena:" << std::endl;
            SpausdintiFailuPavadinimus(failuPavadinimai);

            int index = Console::prasytiInt("Pasirinkite faila:", 1, failuSkaicius);
            failoPavadinimas = failuPavadinimai[index - 1];
        }
    }

    return failoPavadinimas;
}

vector<string> File::PasirinktiFailusFoldery(const string& aplankoVieta, const string& failoTipas) {
    vector<string> pasirinktuFailuPav;

    if (!ArEgzistuojaFailas(aplankoVieta)) {
        std::cout << "Aplankas \"" << aplankoVieta << "\" neegzistuoja." << std::endl;
    }
    else if (!ArYraAplankas(aplankoVieta)) {
        std::cout << "\"" << aplankoVieta << "\" nera aplankas." << std::endl;
    }
    else {
        vector<string> failuPavadinimai = FailuPavadinimaiAplanke(aplankoVieta, failoTipas);
        int failuSkaicius = failuPavadinimai.size();
        if (failuSkaicius == 0) {
            std::cout << "Aplankas \"" << aplankoVieta << "\" nera failu su tokia pabaiga \"" << failoTipas << "\"." << std::endl;
        }
        else if (failuSkaicius == 1) {
            pasirinktuFailuPav.push_back(failuPavadinimai[0]);
        }
        else {
            std::sort(failuPavadinimai.begin(), failuPavadinimai.end());
            std::cout << "Aplanke \"" << aplankoVieta << "\" yra keletas failu. Pasirinkite viena:" << std::endl;

            SpausdintiFailuPavadinimus(failuPavadinimai);
            vector<int> skaiciai = Console::prasytiIntu("Pasirinkite kelis failus:", 1, failuPavadinimai.size());
            for (int i = 0, il = skaiciai.size(); i < il; i++) {
                pasirinktuFailuPav.push_back(failuPavadinimai[skaiciai[i] - 1]);
            }
        }
    }

    return pasirinktuFailuPav;
}