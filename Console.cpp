#include "Console.hpp"

void Console::clearErrorFlagFunkcija() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Console::patvirtinti(const string& pranesimas, char taip, char ne) {
    while (true) {
        std::cout << "-> " << pranesimas << " (" << taip << "/" << ne << "): ";

        char atsakas;
        std::cin >> atsakas;
        clearErrorFlagFunkcija();
        if (atsakas == taip) {
            return true;
        }
        else if (atsakas == ne) {
            return false;
        }
        else {
            std::cout << "Nezinomas simbolis. ";
        }
    }
}

int Console::prasytiInt(const string& pranesimas, int min, int max, int krastVerte) {
    while (true) {
        std::cout << "-> " << pranesimas << " (" << min << "-" << max << "): ";

        int verte;
        std::cin >> verte;
        clearErrorFlagFunkcija();
        if (verte == krastVerte) {
            return krastVerte;
        }
        else if (verte >= min && verte <= max) {
            return verte;
        }
        else {
            std::cout << "Verte neatitinka intervalo. ";
        }
    }
}

vector<int> Console::prasytiIntu(const string& pranesimas, int min, int max) {
    std::cout << "-> " << pranesimas << " (" << min << "-" << max << "): ";
    string eilute;
    getline(std::cin, eilute);

    std::stringstream iss(eilute);
    int skaicius;
    vector<int> skaiciai;

    while (iss >> skaicius) {
        if (skaicius >= min && skaicius <= max) {
            skaiciai.push_back(skaicius);
        }
        else {
            std::cout << skaicius << " nera intervale." << std::endl;
            return prasytiIntu(pranesimas, min, max);
        }
    }

    return skaiciai;
}

string Console::prasytiString(const string& pranesimas) {
    string rezultatas;
    std::cout << "-> " << pranesimas;
    getline(std::cin, rezultatas);
    return rezultatas;
}