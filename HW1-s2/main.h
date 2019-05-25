#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <ios>
#include <limits>
#include <exception>

using namespace std;
namespace fs = experimental::filesystem;

vector<string> split(string s, string delimiter);
string ReplaceAll(string str, const string& from, const string& to);

class Student {
protected:
	string fio;
	string cathedra;
	int semester;
public:
	Student(string fio, string cathedra, int semester)
	{
		this->fio = fio;
		this->cathedra = cathedra;
		this->semester = semester;
	}
	virtual string getFIO();
	virtual int getSemester();
	virtual string toString() = 0;
};

bool operator==(Student& a, Student& b);

bool operator==(Student& a, string name);

bool compareFio(Student* i1, Student* i2);

bool compareSemester(Student* i1, Student* i2);

class OverallStudents : public Student {
	map<string, int>* marks;
public:
	OverallStudents(string fio, string cathedra, int semester) : Student(fio, cathedra, semester) {
		this->fio = fio;
		this->cathedra = cathedra;
		this->semester = semester;
		this->marks = new map<string, int>[this->semester];
	}
	void setMarks(int, string, int);
	string toString() override;
	static OverallStudents fromString(string);
	bool equalSub(string);
	bool excellent();
};

class IndividualStudents : public Student {
	map<string, int> marks;
public:
	IndividualStudents(string fio, string cathedra, int semester) : Student(fio, cathedra, semester) {
		this->fio = fio;
		this->cathedra = cathedra;
		this->semester = semester;
	}
	void addSubjects(vector<string>);
	void addSubject(string);
	void setMark(string, int);
	int getMark(string);
	string toString() override;
	static IndividualStudents fromString(string data);
	bool equalSub(string);
	bool excellent();
};

class DataBase {
	string name;
public:
	DataBase(string);
	void save(const vector<Student*> &);
	void save(const vector<Student*>& students, bool key);
	void sortDB(bool);
	vector<Student*> getData();
	vector<Student*> searchbyName(string);
	vector<Student*> searchbySub(string);
	int countEcellent();
	bool remove(string);
};