#include "main.h"

void OverallStudents::setMarks(int numSem, string subject, int mark)
{
	this->marks[numSem][subject] = mark;
}

string OverallStudents::toString()
{
	string res = "OverallStudents{" + this->fio + ";" + this->cathedra + ";" + to_string(this->semester) + ";";
	for (int i = 0; i < this->semester; i++) {
		for (map<string, int>::iterator jt = this->marks[i].begin(); jt != this->marks[i].end(); jt++) {
			if (jt != this->marks[i].begin())
				res += ",";
			res += jt->first + "=" + to_string(jt->second);
		}
		if (i != this->semester - 1) {
			res += ";";
		}
	}
	res += "}";
	return res;
}

OverallStudents OverallStudents::fromString(string data)
{
	vector<string> v = split(data, ";");
	OverallStudents sd(ReplaceAll(v[0], "OverallStudents{", ""), v[1], atoi(v[2].c_str()));
	for (int i = 3; i < v.size(); i++) {
		vector<string> v1 = split(v[i], ",");
		vector<string> v2;
		for (int j = 0; j < v1.size(); j++) {
			v2 = split(v1[j], "=");
			sd.setMarks(i - 3, v2[0], atoi(v2[1].c_str()));
		}
	}
	return sd;
}

bool OverallStudents::equalSub(string subject)
{
	for (int i = 0; i < this->semester; i++) {
		for (map<string, int>::iterator jt = this->marks[i].begin(); jt != this->marks[i].end(); jt++) {
			if (jt->first == subject)
				return true;
		}
	}
	return false;
}

bool OverallStudents::excellent()
{
	int sch = 0;
	for (map<string, int>::iterator jt = this->marks[this->semester-1].begin(); jt != this->marks[this->semester-1].end(); jt++) {
		if (jt->second == 5)
			sch++;
	}
	if (sch == this->marks[this->semester - 1].size())
		return true;
	return false;
}
