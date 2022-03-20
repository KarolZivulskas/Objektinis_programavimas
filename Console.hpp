#pragma once

#include <iostream>
#include <limits> 
#include <sstream> 
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Console {
	void clearErrorFlagFunkcija(); //clearLine
	bool patvirtinti(const string&, char = 'y', char = 'n'); //confirm
	int prasytiInt(const string&, int, int, int = -100); //promptForInt
	vector<int> prasytiIntu(const string&, int, int); //promptForInts
	string prasytiString(const string&); // promptForString
}