#include "Math.hpp"

double Math::VidurkioSkaiciavimas(vector<int>& masyvas) {
    if (masyvas.empty()) {
        return 0;
    }

    const int masyvoDydis = masyvas.size();
    int sum = 0;
    for (int i = 0; i < masyvoDydis; i++) {
        sum += masyvas[i];
    }

    return (double)sum / masyvoDydis;
}

double Math::MedianosPaieska(vector<int>& masyvas) {
    if (masyvas.empty()) {
        return 0;
    }

    sort(masyvas.begin(), masyvas.end());

    const int masyvoDydis = masyvas.size();
    const bool ArVidurinis = masyvoDydis % 2 != 0;

    if (ArVidurinis) {
        return (double)masyvas[masyvoDydis / 2];
    }

    return (double)(masyvas[(masyvoDydis - 1) / 2] + masyvas[masyvoDydis / 2]) / 2.0;
}