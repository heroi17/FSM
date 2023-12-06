// FSM.cpp: определяет точку входа для приложения.
//

#include "FSM.h"

using namespace std;

int generate(string name, int how_simbols) {
	ofstream out;
	out.open(name);
	if (out.is_open())
	{
		for (int i = 0; i < how_simbols; i++) {
			// rand in [32, 255]
			out << (char)(rand() % (122 - 65) + 65);
		}
	}
	else {
		cout << "Fail with open file: " << name << endl;
	}
	out.close();
	return 0;
}

string open_as_string(string name) {
	ifstream in;
	string str;
	char c;
	in.open(name);
	if (in.is_open())
	{
		while (in.get(c)) {
			str += c;
		}
	}
	else cout << "Fail with open file: " << endl;
	return str;
}


int main()
{
	//make file with simbols
	string name = "test.txt";
	int how_symbols = 10000;
	//generate(name, how_symbols);
	string string_data = open_as_string(name);
	//cout << string_data;
	if (IsStringIn(string_data, "My family is very important")) {
		cout << "Substring is finded in text." << endl;
	}
	else {
		cout << "Substring is not finded in this text." << endl;
	}


	//FSM myFSM = FSM();
	//myFSM.printMe();




	return 0;
}


