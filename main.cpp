#include <iostream>
#include <sstream> 
#include <string>
#include <vector>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "RND.hpp" 
#include "Student.hpp"
#include "Table.hpp"
#include "Timer.hpp"

#define GRADE_MIN 1
#define GRADE_MAX 10

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

string NustatytiRezTipa()
{
    int promptResult = Console::PrasytiInt("Choose what to calculate: (1)Mean, (2)Median, (3)Both:", 1, 3);

    string rezTipas = RESULT_TYPE_BOTH;
    if (promptResult == 1)
    {
        rezTipas = RESULT_TYPE_MEAN;
    }
    else if (promptResult == 2)
    {
        rezTipas = RESULT_TYPE_MEDIAN;
    }

    return rezTipas;
}

void printRandomGrades(Student::Studentas& studentas)
{
    const int masyvoDydis = studentas.pazymiai.size();
    cout << "Generated " << masyvoDydis << " random grades: ";
    for (int i = 0; i < masyvoDydis; i++)
    {
        cout << studentas.pazymiai[i] << " ";
    }
    cout << endl;
    cout << "Generated random exam grade: " << studentas.egzamino << endl;
}

void Grades_EnterManually(bool numberOfGradesIsKnown, int pazymiuSk, Student::Studentas& studentas)
{
    if (numberOfGradesIsKnown)
    {
        if (pazymiuSk > 0)
        {
            while (studentas.pazymiai.size() != pazymiuSk)
            {
                int grade = Console::PrasytiInt("Enter grade", GRADE_MIN, GRADE_MAX);
                studentas.pazymiai.push_back(grade);
            }
        }
    }
    else
    {
        while (true)
        {
            int grade = Console::PrasytiInt(
                "Enter grade (type -1 to quit)", GRADE_MIN, GRADE_MAX, -1);
            if (grade == -1)
            {
                break;
            }
            else
            {
                studentas.pazymiai.push_back(grade);
            }
        }
    }

    studentas.egzamino = Console::PrasytiInt("Enter exam grade", GRADE_MIN, GRADE_MAX);
}

void Grades_GenerateRandomly(bool numberOfGradesIsKnown, int pazymiuSk, Student::Studentas& studentas)
{
    if (numberOfGradesIsKnown)
    {
        for (int i = 0; i < pazymiuSk; i++)
        {
            int grade = RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX);
            studentas.pazymiai.push_back(grade);
        }
    }
    else
    {
        while (true)
        {
            int grade = RND::GeneruotiAtsitiktiniIntervale(0, GRADE_MAX);
            if (grade == 0)
            {
                break;
            }
            else
            {
                studentas.pazymiai.push_back(grade);
            }
        }
    }
    studentas.egzamino = RND::GeneruotiAtsitiktiniIntervale(GRADE_MIN, GRADE_MAX);
    printRandomGrades(studentas);
}

void Grades_ReadFromFile(const string& failoVieta, vector<Student::Studentas>& studentai)
{
    Timer timer;
    timer.start();

    stringstream buffer = File::GrazintiBuferi(failoVieta);
    cout << "Buferinimo laikas: " << timer.elapsed() << endl;
    timer.reset();

    string line;
    getline(buffer, line);
    while (getline(buffer, line))
    {
        Student::Studentas studentas;

        stringstream iss(line);
        iss >> studentas.vardas >> studentas.pavarde;

        int grade;
        while (iss >> grade)
        {
            studentas.pazymiai.push_back(grade);
        }

        studentas.pazymiai.pop_back();
        studentas.egzamino = grade;

        studentai.push_back(studentas);
    }

    cout << "Reading data from file took " << timer.elapsed() << endl;
}

void Data_EnterManually(vector<Student::Studentas>& studentai)
{
    while (true)
    {
        Student::Studentas studentas;
        studentas.vardas = Console::PrasytiString("Iveskite varda: ");
        studentas.pavarde = Console::PrasytiString("Iveskite pavarde: ");

        int pazymiuSk = 0;
        const bool numberOfGradesIsKnown = Console::patvirtinti("Do you know the number of grades?");
        if (numberOfGradesIsKnown)
        {
            pazymiuSk = Console::PrasytiInt("Enter number of grades", 0, 100);
        }

        bool shouldGenerateRandomGrades = false;
        if (!numberOfGradesIsKnown || pazymiuSk > 0)
        {
            shouldGenerateRandomGrades = Console::patvirtinti("Generate RANDOM grades (otherwise, enter grades MANUALLY)?");
        }

        if (shouldGenerateRandomGrades)
        {
            Grades_GenerateRandomly(numberOfGradesIsKnown, pazymiuSk, studentas);
        }
        else
        {
            Grades_EnterManually(numberOfGradesIsKnown, pazymiuSk, studentas);
        }

        studentai.push_back(studentas);
        if (!Console::patvirtinti("Ar norite prideti dar viena studenta?"))
        {
            break;
        }
    }
}

void Data_ReadFromFile(vector<Student::Studentas>& studentai)
{
    string failoTipas = "txt";
    string aplankoVieta = "./data/";
    string failoVieta = File::PasirinktiFailaAplanke(aplankoVieta, failoTipas);
    if (failoVieta.empty())
    {
        const bool shouldEnterManually = Console::patvirtinti(
            "Do you want to enter grades manually instead?:");

        if (shouldEnterManually)
        {
            cout << "Switching to manual mode." << endl;
            Data_EnterManually(studentai);
        }
        else
        {
            cout << "Terminating program." << endl;
        }
    }
    else
    {
        failoVieta = aplankoVieta + failoVieta;
        cout << "Reading data from \"" << failoVieta << "\"" << endl;
        Grades_ReadFromFile(failoVieta, studentai);
    }
}

int main()
{
    vector<Student::Studentas> studentai;

    const bool shouldReadFromFile = Console::patvirtinti(
        "(y)Read grades from file; (n)Enter grades manaully:");

    try
    {
        if (shouldReadFromFile)
        {
            Data_ReadFromFile(studentai);
        }
        else
        {
            Data_EnterManually(studentai);
        }

        if (studentai.size() > 0)
        {
            string rezTipas = NustatytiRezTipa();
            Student::SutvarkytiStudentus(studentai, rezTipas);

            cout << endl;
            Table::SpausdintiRezultatus(studentai, rezTipas);
            cout << endl;
        }

        return 0;
    }
    catch (std::exception& error)
    {
        std::cerr << error.what() << endl;
    }
}