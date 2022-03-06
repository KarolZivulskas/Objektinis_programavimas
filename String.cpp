#include "String.hpp"

bool String::ArTuriPriesaga(const std::string& str, const std::string& priesaga) {
    return str.size() >= priesaga.size() &&
        str.compare(str.size() - priesaga.size(), priesaga.size(), priesaga) == 0;
}
