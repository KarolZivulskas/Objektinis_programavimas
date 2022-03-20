#include "String.hpp"

bool String::ArTuriPriesaga(const std::string& str, const std::string& priesaga) {
    unsigned long stringoDydis = str.size();
    unsigned long priesagosDydis = priesaga.size();

    return stringoDydis >= priesagosDydis &&
        str.compare(stringoDydis - priesagosDydis, priesagosDydis, priesaga) == 0;
}