#pragma once

#include "Console.hpp"
#include "RND.hpp"
#include "Student.hpp"

namespace Grades {
	void IvestiRankiniuBudu(bool, int, Student::Studentas&); //enterManually
	void GeneruotiAtsitiktinai(bool, int, Student::Studentas&); //generateRandomly
}