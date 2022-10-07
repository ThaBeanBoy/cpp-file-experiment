#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "exceptions.h"

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
	string file = "data/people.txt";
	system("cls");

	cout << "Please select 1 of the following actions:" << endl
		<< "1. Add a user to the file." << endl
		<< "2. Display all the users" << endl << endl
		<< "Choice : ";

	int action;
	cin >> action;

	if (action == 1) {
		system("cls");
		string name;
		string surname;
		cout << "New User" << endl
			<< "\tName : ";
		cin >> name;
		cout << endl
			<< "\tSurname : ";
		cin >> surname;

		// Save the user
		ofstream out_f_stream;
		out_f_stream.open(file, ios::app);

		out_f_stream << "\n" << name << " " << surname;

		out_f_stream.close();

	}
	else {
		system("cls");

		try {
			vector<Person> users = getUsersFromFile(file);

			for (Person user : users) {
				cout << "Name    : " << user.getName() << endl
					<< "Surname : " << user.getSurname() << endl << endl;
			}
		}
		catch (loadFileException& err) {
			cerr << "Failed to load properly";
			exit(-1);
		}
	}

	return 0;
}

vector<Person> getUsersFromFile(string fileName) {
	vector<Person> users;
	ifstream in_stream;
	in_stream.open(fileName);

	if (in_stream.fail()) {
		throw loadFileException();
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

