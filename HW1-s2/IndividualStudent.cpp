#include "main.h"

void IndividualStudents::addSubjects(vector<string> subjects)
{
	for (int i = 0; i < subjects.size(); i++)
		this->marks[subjects[i]] = 0;

}

void IndividualStudents::addSubject(string subject)
{
	this->marks[subject] = 0;
}

void IndividualStudents::setMark(string subject, int mark)
{
	if (this->marks.find(subject) == this->marks.end() || mark < 2 || mark>5)
		return;
	this->marks[subject] = mark;
}

int IndividualStudents::getMark(string subject)
{
	if (this->marks.find(subject) == this->marks.end())
		return 0;
	return this->marks[subject];
}

string IndividualStudents::toString()
{
	string res = "IndividualStudents{" + this->fio + ";" + this->cathedra + ";" + to_string(this->semester);
	for (auto i = this->marks.begin(); i != this->marks.end(); i++)
		res += ";" + i->first + "=" + to_string(i->second);
	res += "}";
	return res;
}

IndividualStudents IndividualStudents::fromString(string data)
{
	vector<string> tmp = split(data, ";");
	IndividualStudents res(ReplaceAll(tmp[0], "IndividualStudents{", ""), tmp[1], atoi(tmp[2].c_str()));
	for (int i = 3; i < tmp.size(); i++) {
		vector<string> tmp2 = split(tmp[i], "=");
		vector<string> subjects;
		for (auto jt = tmp2.begin(); jt != tmp2.end();)
		{
			res.addSubject(*jt);
			subjects.push_back(*jt);
			jt = tmp2.erase(jt) + 1;
		}
		for (int j = 0; j < subjects.size(); j++)
			res.setMark(subjects[j], stoi(tmp2[j]));
	}
	return res;
}

bool IndividualStudents::equalSub(string subject)
{
	vector<string> subjects;
	for (auto &i : this->marks)
		subjects.insert(subjects.begin(), i.first);
	for (int i = 0; i < this->marks.size(); i++) {
		if (subject == subjects[i])
			return true;
	}
	return false;
}

bool IndividualStudents::excellent()
{
	int sch = 0;
	vector<string> subjects;
	for (auto &i : this->marks)
		subjects.insert(subjects.begin(), i.first);
	for (int i = 0; i < subjects.size(); i++) {
		if (this->getMark(subjects[i]) == 5)
			sch++;
	}
	if (sch == subjects.size())
		return true;
	return false;
}