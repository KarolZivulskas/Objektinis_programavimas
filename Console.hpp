#pragma once

#include <iostream>
#include <limits>
#include <string>

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::string;

namespace Console {
	void clearErrorFlagFunkcija();
	bool patvirtinti(const string&, char = 'y', char = 'n');
	int PrasytiInt(const string&, int, int, int = -100);
	string PrasytiString(const string&);
}