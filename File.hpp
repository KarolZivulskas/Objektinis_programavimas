#pragma once

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Console.hpp"
#include "String.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::vector;

namespace File {
	bool ArEgzistuojaFailas(const string&);
	stringstream GrazintiBuferi(const string&);
	vector<string> FailuPavadinimai(const string&, const string&);
	bool ArYraFailas(const string&);
	bool ArYraAplankas(const string&);
	string PasirinktiFailaAplanke(const string&, const string&);
}