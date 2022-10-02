#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Person {
public:
	Person(string name = "", string surname = "") : _name(name), _surname(surname) {}

	string getName() {
		return _name;
	}

	string getSurname() {
		return _surname;
	}

private:
	string _name;
	string _surname;
};

vector<Person> getUsersFromFile(string fileName);

int main() {
	system("cls");

	// ofstream out_f_stream;
	// out_f_stream.open("Dummy.txt");

	// out_f_stream.close();

	vector<Person> UsersFromFile = getUsersFromFile("data/people.txt");
	cout << "name : " << UsersFromFile[0].getName();

	return 0;
}

vector<Person> getUsersFromFile(string fileName) {
	vector<Person> users;
	ifstream in_stream;
	in_stream.open(fileName);

	if (in_stream.fail()) {
		cerr << "There was an error with opening the file.";
		exit(-1);
	}

	string userLine = "";
	while (getline(in_stream, userLine)) {
		stringstream ssLine{ userLine };

		string name = "";
		string surname = "";
		ssLine >> name;
		ssLine >> surname;

		users.push_back(Person(name, surname));
	}

	in_stream.close();
	return users;
}