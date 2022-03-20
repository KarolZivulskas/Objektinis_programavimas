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
	bool ArEgzistuojaFailas(const string&); //fileExists
	string getBaseName(const string&); //getBaseName
	stringstream GrazintiBuferi(const string&); // getBuffer
	vector<string> FailuPavadinimaiAplanke(const string&, const string&); //getFilenamesInFolder
	bool ArYraFailas(const string&);// __unused bool isFile
	bool ArYraAplankas(const string&); // isFolder
	void IssaugotiBuferi(const string&, stringstream&); // saveBuffer
	string PasirinktiFailaFoldery(const string&, const string&); //selectFileInFolder
	vector<string> PasirinktiFailusFoldery(const string&, const string&);//selectFilesInFolder
}
