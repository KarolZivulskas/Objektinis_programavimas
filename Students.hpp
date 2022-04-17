#pragma once

#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "Comparator.hpp"
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
using std::deque;
using std::endl;
using std::fixed;
using std::left;
using std::list;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;

namespace Students {
	void Filtruoti(const string&, const string&, const int&);
	void GeneruotiIrasus(int);

	template <class A>
	void SpausdintiFormatuota(A&, const string&);

	template <class A>
	void SutvarkytiStudentus(A&, const string&);

	template <class A>
	void SkaitytiIsFailo(const string&, A&);

	template <class A>
	void Issaugoti(A&, const string&);

	template <class A>
	void RikiuotiPagalGalutiniMazejant(A&);
	void RikiuotiPagalGalutiniMazejant(list<Student::Studentas>&);

	template <class A>
	void RikiuotiPagalVardaDidejant(A&);
	void RikiuotiPagalVardaDidejant(list<Student::Studentas>&);
}