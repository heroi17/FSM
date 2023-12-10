#include <iostream>
#include <fstream>
#include "console_menu.h"
#include "../FIND_STRING/FIND_STRING.h"

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
	else cout << "Fail with open file: " << name << endl;
	return str;
}


bool exit_function(vector<string> arguments, menu* current_menu) {
	current_menu->going_loop = false;
	return true;
}
bool output_file(vector<string> arguments, menu* current_menu){
	if (arguments.size() != 1) return false;
	string name = arguments[0];
	string string_data = open_as_string(name);
	cout << string_data << endl;
}

bool isStringIn(vector<string> arguments, menu* current_menu) {
	if (arguments.size() < 2) return false;
	//make file with simbols
	string name = arguments[0];
	//int how_symbols = 10000;
	//generate(name, how_symbols);
	string string_data = open_as_string(name);
	if (string_data.size() == 0) return true;
	//cout << string_data;
	string substring;
	arguments.erase(arguments.begin());
	for (auto const c : arguments)
		substring += c + " ";
	substring.pop_back();
	if (IsStringIn(string_data, substring)) {
		cout << "Substring is finded in text." << endl;
	}
	else {
		cout << "Substring is not finded in this text." << endl;
	}
	return true;
}


state_start_menu::state_start_menu() {
	menu_information.push_back("You in start menu of finding string into big txt file.");
	menu_information.push_back("Exist one test file: --(test.txt)-- txt file.");
	menu_information.push_back("To call func print his name and argument separated by spaces");
	menu_information.push_back("F - find substring in txt file with argument: filename.txt, substring");
	menu_information.push_back("O - output txt file in console with argument: filename.txt");
	menu_information.push_back("E - without arguments");
	function_map["E"] = &exit_function;
	function_map["F"] = &isStringIn;
	function_map["O"] = &output_file;
}