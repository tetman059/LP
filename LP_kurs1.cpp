#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Family { // структура для предиката
	string Child;
	string Mother;
	string Father;
};

void clear_family(Family& family) { // очистка переменной
	family.Child.clear();
	family.Mother.clear();
	family.Father.clear();
}

void GeneratePred(const vector<Family>& families, ofstream& output) { // создаем предикат, который запишем в output
	for (const auto& item : families) {
		string pred = "parents(" + item.Child + ", " + item.Father + ", " + item.Mother + ")";
		output << pred << endl;
	}
}

#define GET_LINE(stream_size) {		\
	istringstream is(line);			\
	is.ignore(stream_size);			\
	getline(is, id, '@');			\
}

int main() {
	map<string, string> persons; // словарь с парой id - имя
	vector<Family> families;
	string id;
	string person; // считываемое имя, которое затем будет добавлено в persons
	Family family;

	ifstream input("C:\\Users\\User\\Downloads\\tree.ged");
	ofstream output("prolog.txt");
	string line; // переменная, в которую будем считывать
	if (input) {
		while (getline(input, line)) {
			if (line[0] == '0' && line[12] == 'I') {
				id.clear();
				person.clear();
				GET_LINE(3)
			} else if (line.substr(0, 6) == "1 NAME") {
				person = line.substr(7);
				persons[id] = person;
			} else if (line.substr(0, 4) == "0 @F") {
				id.clear();
				clear_family(family);
			} else if (line.substr(0, 6) == "1 HUSB") {
				GET_LINE(8)
				family.Father = persons.at(id);
			} else if (line.substr(0, 6) == "1 WIFE") {
				GET_LINE(8);
				family.Mother = persons.at(id);
			} else if (line.substr(0, 6) == "1 CHIL") {
				GET_LINE(8)
				family.Child = persons.at(id);
				families.push_back(family);
			}
		}
	} else {
		cout << "Input the correct path" << endl;
	}

	GeneratePred(families, output);
	cout << "Done!" << endl;
	return 0;
}
