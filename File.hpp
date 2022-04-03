#pragma once

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Console.hpp"
#include "String.hpp"

using std::string;
using std::stringstream;
using std::vector;

namespace File {
	bool ArEgzistuojaFailas(const string&);
	string getBaseName(const string&);
	stringstream GrazintiBuferi(const string&);
	vector<string> FailuPavadinimaiAplanke(const string&, const string&);
	[[maybe_unused]] bool ArYraFailas(const string&);
	bool ArYraAplankas(const string&);
	void IssaugotiBuferi(const string&, stringstream&);
	string PasirinktiFailaFoldery(const string&, const string&);
	vector<string> PasirinktiFailusFoldery(const string&, const string&);
}