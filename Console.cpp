#include "Console.hpp"

void Console::clearErrorFlagFunkcija() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool Console::patvirtinti(const string& pranesimas, char taip, char ne) {
    while (true) {
        cout << "-> " << pranesimas << " (" << taip << "/" << ne << "): ";

        char atsakas;
        cin >> atsakas;
        clearErrorFlagFunkcija();
        if (atsakas == taip) {
            return true;
        }
        else if (atsakas == ne) {
            return false;
        }
        else {
            cout << "Netinkamas simbolis ";
        }
    }
}

int Console::PrasytiInt(const string& pranesimas, int min, int max, int krastVerte) {
    while (true) {
        cout << "-> " << pranesimas << " (" << min << "-" << max << "): ";

        int verte;
        cin >> verte;
        clearErrorFlagFunkcija();
        if (verte == krastVerte) {
            return krastVerte;
        }
        else if (verte >= min && verte <= max) {
            return verte;
        }
        else {
            cout << "Verte neatitinka pazymiu intervalo ";
        }
    }
}

string Console::PrasytiString(const string& pranesimas) {
    string rezultatas;
    cout << "-> " << pranesimas;
    getline(cin, rezultatas);
    return rezultatas;
}