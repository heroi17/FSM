#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
using namespace std;
class menu;





class state {
public:
	map<string, bool(*)(vector<string>, menu*)> function_map;
	vector<string> menu_information;
	vector<string> get_information(){
		return menu_information;
	}
};


class state_start_menu : public state {
public:
	state_start_menu();
};

class state_exit_menu : public state {
public:
	state_exit_menu() {
		menu_information.push_back("asdas");
	}
};



class menu {
public:
	state* current_state;
	bool going_loop = true;
	void change_menu(state* new_state) {
		delete current_state;
		current_state = new_state;
	}
	vector<string>* get_menu() {
		return &current_state->menu_information;
	}
	/// <summary>
	/// Function divides a sentence into tokens.
	/// First token - is name of func.
	/// The following tokens are the arguments of the function.
	/// </summary>
	void solve_command(vector<string> input_command) {
		
		if (input_command.size() == 0) {
			cout << "your command is empty" << endl;
			return void();
		}
		string command_name = input_command[0];
		//if input function actualy exist zhen we try to call it
		if (current_state->function_map.find(command_name) == current_state->function_map.end()) {
			cout << "this command is none exist" << endl;
			return void();
		}
		//call function and check is funcktion fnished ok or no
		//give her argument and our current menu to change something
		input_command.erase(input_command.begin());
		bool is_solved = (current_state->function_map[command_name])(input_command, this);

		if (is_solved) {cout << "your command is solved." << endl; return void(); }
		else {cout << "your command is none solved." << endl; return void(); }
	}
	void start_menu_loop() {
		current_state = new state_start_menu();
		going_loop = true;
		string input;
		
		while (going_loop) {
			output_menu_information();
			cout << "input: ";
			vector<string> input_command;
			{
				std::string inputString;
				std::getline(cin, inputString);
				std::istringstream iss(inputString);
				std::string word;
				while (iss >> word) {
					input_command.push_back(word);
				}
			}
			solve_command(input_command);
			cout << "---------------------------------------------------------------" << endl;

		}
	}
	void output_menu_information() {
		vector<string>* text = &(current_state->menu_information);
		for (auto const centence : *text) {
			cout << centence << endl;
		}
	}

};