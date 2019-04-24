#include "main.h"

int Student::getSemester() {
	return this->semester;
}

string Student::getFIO()
{
	return this->fio;
}

string Student::toString()
{
	string res = "{" + this->fio + ";" + this->cathedra + ";" + to_string(this->semester) + "}";
	return res;
}