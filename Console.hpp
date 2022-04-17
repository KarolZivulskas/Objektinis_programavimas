#pragma once

#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Console {
	void clearErrorFlagFunkcija();
	bool patvirtinti(const string&, char = 'y', char = 'n');
	int prasytiInt(const string&, int, int, int = -100);
	vector<int> prasytiIntu(const string&, int, int);
	string prasytiString(const string&);
}