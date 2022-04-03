#include "Utils.hpp"

int Utils::RastiSkaitmenuSkaiciu(int skaicius) {
    int skaitmenuSk = 0;

    while (skaicius > 0) {
        skaitmenuSk++;
        skaicius /= 10;
    }

    return skaitmenuSk;
}