#include "main.h"

DataBase::DataBase(string name) {
	this->name = name;
}

void DataBase::save(const vector<Student*>& students)
{
	ofstream lol(this->name, ios_base::app);
	for (Student* student : students) 
		lol << student->toString() << endl;
}

void DataBase::save(const vector<Student*>& students, bool key)
{
	if (key == true) {
		ofstream lol(this->name);
		for (Student* student : students)
			lol << student->toString() << endl;
	}
	else {
		this->save(students);
	}
}

vector<Student*> DataBase::getData()
{
	vector<Student*> students;
	ifstream loi(this->name);
	string tmp;
	while (getline(loi, tmp)) {
		if (tmp.find("OverallStudents") != string::npos) {
			Student *student = new OverallStudents(OverallStudents::fromString(tmp));
			students.push_back(student);
		}
		else if (tmp.find("IndividualStudents") != string::npos) {
			Student *student = new IndividualStudents(IndividualStudents::fromString(tmp));
			students.push_back(student);
		}
	}
	loi.close();
	return students;
}

void DataBase::sortDB(bool key)
{
	vector<Student*> students = this->getData();
	if(key==true)
		sort(students.begin(), students.end(), compareFio);
	else
		sort(students.begin(), students.end(), compareSemester);
	this->save(students, true);
}

vector<Student*> DataBase::searchbyName(string name)
{
	vector<Student*> students=this->getData();
	vector<Student*> res;
	for (int i = 0; i < students.size(); i++) {
		if (name == students[i]->getFIO())
			res.push_back(students[i]);
	}
	return res;
}

vector<Student*> DataBase::searchbySub(string sub)
{
	vector<Student*> res;
	string tmp;
	ifstream basa(this->name);
	while (getline(basa, tmp)) {
		if (tmp.find("OverallStudents") != string::npos) {
			OverallStudents* student = new OverallStudents(OverallStudents::fromString(tmp));
			if (student->equalSub(sub))
				res.push_back(student);
			
		}
		else if (tmp.find("IndividualStudents") != string::npos) {
			IndividualStudents* student = new IndividualStudents(IndividualStudents::fromString(tmp));
			if (student->equalSub(sub))
				res.push_back(student);
		}
	}
	basa.close();
	return res;
}

int DataBase::countEcellent()
{
	vector<Student*> res;
	int sch = 0;
	string tmp;
	ifstream basa(this->name);
	while (getline(basa, tmp)) {
		if (tmp.find("OverallStudents") != string::npos) {
			OverallStudents* student = new OverallStudents(OverallStudents::fromString(tmp));
			if (student->excellent())
				sch++;

		}
		else if (tmp.find("IndividualStudents") != string::npos) {
			IndividualStudents* student = new IndividualStudents(IndividualStudents::fromString(tmp));
			if (student->excellent())
				sch++;
		}
	}
	basa.close();
	return sch;
}


bool DataBase::remove(Student* student)
{
	vector<Student*> list = this->getData();
	for (int i = 0; i < list.size(); i++) {
		if (*student == *list[i]) {
			list.erase(list.begin()+i);
			this->save(list, true);
			return true;
		}
	}
	return false;
}