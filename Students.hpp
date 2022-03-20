#pragma once

#include <algorithm>
#include <iomanip> 
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "Grades.hpp"
#include "RND.hpp"
#include "Student.hpp"
#include "Table.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;

namespace Students {
	void Filtruoti(const string&); //filter
	void GeneruotiIrasus(int); //generateRecords
	void SpausdintiFormatuota(vector<Student::Studentas>&, const string&); //printFormatted
	void SutvarkytiStudentus(vector<Student::Studentas>&, const string&); //processStudents
	void SkaitytiIsFailo(const string&, vector<Student::Studentas>&); //readFromFile
	void Issaugoti(vector<Student::Studentas>&, const string&); //save
	void RikiuotiPagalGalutiniMazejant(vector<Student::Studentas>&); //sortbyfinalgradedescending
	void RikiuotiPagalVardaDidejant(vector<Student::Studentas>&); //sortbynameascending
}