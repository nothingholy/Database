#include "main.h"

vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

string ReplaceAll(string str, const string& from, const string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
	return str;
}

bool operator==(Student& a, Student& b) {
	return a.getFIO() == b.getFIO() && a.getSemester() == b.getSemester();
}

bool operator==(Student& a, string name) {
	return a.getFIO() == name;
}

bool compareFio(Student* i1, Student* i2) {
	return i1->getFIO() < i2->getFIO();
}

bool compareSemester(Student* i1, Student* i2) {
	return i1->getSemester() < i2->getSemester();
}

void show() {
	cout << "Databases:" << endl;
	std::string path = ".";
	for (const auto & entry : fs::directory_iterator(path)) {
		if (entry.path().extension().string() == ".txt") {
			cout << entry.path().string() << endl;
		}
	}
}

void showDB(string name) {
	cout << name << " :" << endl;
	string loi;
	ifstream shkila;
	shkila.open(name + ".txt");
	if (!shkila) {
		cout << "Error!Unable to open file" << endl;
	}
	while (shkila >> loi)
		cout << loi << endl;
	shkila.close();
}

void help() {
	cout << "To create new DB enter: create <DB name>" << endl;
	cout << "To show database enter: show <DB name>" << endl;
	cout << "To show list of DBs enter: view" << endl;
	cout << "To edit DB enter: edit <DB name>" << endl;
	cout << "To sort DB enter: sort <DB name>" << endl;
	cout << "To count the excellent students enter: count <DB name>" << endl;
	cout << "To delete student in DB enter: delete <DB name>" << endl;
	cout << "To choose students in DB enter: choose <DB name1> <DB name2>" << endl;
	cout << "To exit DB redactor enter: exit" << endl;
}

void create(string loiname) {
	DataBase loi(loiname + ".txt");
	loi.save({});
}

void edit(string name) {
	showDB(name);
	while (true)
	{
		cout << "What kind of student do u want to add overall or individual or exit?" << endl;
		string answer;
		cin >> answer;
		if (answer == "overall") {
			string fio, cathedra;
			int semester,quantitysub;
			cout << "Enter fio: " << endl;
			cin.ignore();
			getline(cin, fio);
			cout << "Enter cathedra: "; getline(cin, cathedra);
			cout << "Enter semester: "; 
			while (true) {
				cin >> semester;
				if (cin.fail()) {
					cout << "Error!Try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
					break;
			}
			OverallStudents* student = new OverallStudents(fio, cathedra, semester);
			int quantity;
			for (int i = 0; i < student->getSemester(); i++) {
				cout << "Enter quantity of subjects: ";
				while (true) {
					cin >> quantity;
					if (cin.fail()) {
						cout << "Error!Try again" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else
						break;
				}
				string sub;
				int mark;
				for (int j = 0; j < quantity; j++) {
					cout << "Enter subject: ";
					cin.ignore();
					getline(cin, sub);
					cout << "Enter mark: ";
					while (true) {
						cin >> mark;
						if (cin.fail()) {
							cout << "Error!Try again" << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						else
							break;
					}
					student->setMarks(i, sub, mark);
				}
			}
			DataBase loi1(name + ".txt");
			loi1.save({ student });
		}
		else if (answer == "individual") {
			string fio, cathedra;
			int semester, quantitysub;
			cout << "Enter fio:" << endl; 
			cin.ignore();
			getline(cin, fio);
			cout << "Enter cathedra: "; getline(cin, cathedra);
			cout << "Enter semester: "; 
			while (true) {
				cin >> semester;
				if (cin.fail()) {
					cout << "Error!Try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
					break;
			}
			cout << "Enter quantity of subjects: ";
			while (true) {
				cin >> quantitysub;
				if (cin.fail()) {
					cout << "Error!Try again" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
					break;
			}
			IndividualStudents* student = new IndividualStudents(fio, cathedra, semester);
			vector<string> subjects;
			subjects.resize(quantitysub);
			cout << "Enter subjects:" << endl;
			for (auto &i : subjects)
				cin >> i;
			student->addSubjects(subjects);
			for (int i = 0; i < subjects.size(); i++) {
				int mark;
				cout << "Enter mark for " << subjects[i] << " :";
				while (true) {
					cin >> mark;
					if (cin.fail()) {
						cout << "Error!Try again" << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					else
						break;
				}
				student->setMark(subjects[i], mark);
			}
			DataBase loi1(name + ".txt");
			loi1.save({ student });
		}
		else if (answer == "exit")
			break;
		else {
			cout << "Error!Wrong command!" << endl;
		}
	}
}

void sortDB(string name) {
	ifstream shkila;
	string str;
	shkila.open(name + ".txt");
	if (!shkila) {
		cout << "Error!Unable to open file" << endl;
		return;
	}
	bool key;
	cout << "Sort by name(1) or by semester(0)" << endl;
	while (true) {
		cin >> key;
		if (cin.fail()) {
			cout << "Error!Try again" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
			break;
	}
	DataBase loi(name + ".txt");
	loi.sortDB(key);
	cout << "DB was succesfully sorted!" << endl;
}

void countExecellent(string name) {
	ifstream shkila;
	shkila.open(name + ".txt");
	if (!shkila) {
		cout << "Error!Unable to open file" << endl;
		return;
	}
	shkila.close();
	DataBase loi(name + ".txt");
	cout << "The execellent students: " << loi.countEcellent() << endl;
}

void choose(string namef,string namet) {
	ifstream shkila, shkila1;
	string str;
	shkila.open(namef + ".txt");
	if (!shkila) {
		cout << "Error!Unable to open file" << endl;
		return;
	}
	while (shkila >> str)
		cout << str << endl;
	shkila.close();
	shkila1.open(namet + ".txt");
	if (!shkila1) {
		cout << "Error!Unable to open file" << endl;
		return;
	}
	shkila1.close();
	while (true) {
		string ans;
		cout << "Choose by name or by subject or exit?" << endl;
		getline(cin, ans);
		if (ans == "name") {
			string name;
			cout << "Enter name: "; getline(cin, name);
			DataBase loi(namef + ".txt"), loi2(namet + ".txt");
			if (loi.searchbyName(name).size() == 0) {
				cout << "No such name" << endl;
			}
			loi2.save(loi.searchbyName(name));
		}
		else if (ans == "subject") {
			string subject;
			cout << "Enter subject: "; getline(cin, subject);
			DataBase loi(namef + ".txt"), loi2(namet + ".txt");
			if (loi.searchbySub(subject).size() == 0) {
				cout << "No such subject" << endl;
			}
			loi2.save(loi.searchbySub(subject));
		}
		else if (ans == "exit") {
			break;
		}
		else
			cout << "Error!Wrong command" << endl;
	}
}

void removeStudent(string name) {
	ifstream shkila;
	shkila.open(name + ".txt");
	if (!shkila) {
		cout << "Error!Unable to open file" << endl;
		return;
	}
	shkila.close();
	string fio, cathedra;
	int semester;
	cout << "Enter fio: "; getline(cin, fio);
	DataBase loi(name + ".txt");
	loi.remove(fio);
}

void start() {
	cout << "Hello,nothingholy!" << endl;
	while (true) {
		try{
			cout << "Command: ";
			string res;
			getline(cin, res);
			vector<string> results;
			if (res != "") {
				results = split(res, " ");
				if (results.size() == 1) {
					if (results[0] == "help")
						help();
					else if (results[0] == "view")
						show();
					else if (results[0] == "exit")
						return;
					else
						throw exception("Wrong command");
				}
				else {
					if (results[0] == "create")
						create(results[1]);
					else if (results[0] == "show")
						showDB(results[1]);
					else if (results[0] == "edit")
						edit(results[1]);
					else if (results[0] == "sort")
						sortDB(results[1]);
					else if (results[0] == "count")
						countExecellent(results[1]);
					else if (results[0] == "delete")
						removeStudent(results[1]);
					else if (results[0] == "choose")
						choose(results[1], results[2]);
					else
						throw exception("Wrong command");
				}
			}
		}
		catch (exception& err)
		{
			cout << "Error:" << err.what() << endl;
		}
	}
}

int main() {
	start();

	system("pause");
	return 0;
}