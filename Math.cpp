#include "Math.hpp"

double Math::VidurkioSkaiciavimas(vector<int>& masyvas) {
    if (masyvas.empty()) {
        return 0;
    }

    return std::accumulate(masyvas.begin(), masyvas.end(), 0.0) / masyvas.size();
}

double Math::MedianosPaieska(vector<int>& masyvas) {
    if (masyvas.empty()) {
        return 0;
    }

    std::sort(masyvas.begin(), masyvas.end());

    const int masyvoDydis = masyvas.size();
    const bool ArVidurinis = masyvoDydis % 2 != 0;

    if (ArVidurinis) {
        return (double)masyvas[masyvoDydis / 2];
    }

    return (double)(masyvas[(masyvoDydis - 1) / 2] + masyvas[masyvoDydis / 2]) / 2.0;
}