#include "FSM_CLASS.h"
using namespace std;
FSM<string, char> ReadFsmFromFile(string filename) {
	vector<string> filedata = readasvec(filename);
	map<string, map<char, string>> rule_map;
	map<string, string> break_map;
	vector<string> current_input;
	bool in_break_state = false;
	int in_break_counter = 0;
	bool in_rule_state = false;
	int in_rule_counter = 0;
	for ( string el : filedata) {
		if (el == "$empty") el = "";
		if (el == "$END") break;
		else if (el == "$START") continue;
		else if (el == "$break_state") {
			in_break_state = true;
			in_break_counter = 0;
			current_input.clear();
		}
		else if (el == "$rule_state") {
			in_rule_state = true;
			in_rule_counter = 0;
			current_input.clear();
		}
		else if (el == "$rule_end") {
			in_rule_state = false;
			in_rule_counter = 0;
			current_input.clear();
		}
		else if (el == "$break_end") {
			in_break_state = false;
			in_break_counter = 0;
			current_input.clear();
		}
		else if (in_rule_state){
			in_rule_counter += 1;
			current_input.push_back(el);
			if (in_rule_counter == 3) {
				rule_map[current_input[0]][current_input[1][0]] = current_input[2];
				current_input.clear();
				in_rule_counter = 0;
			}
		}
		else if (in_break_state) {
			in_break_counter += 1;
			current_input.push_back(el);
			if (in_break_counter == 2) {
				break_map[current_input[0]] = current_input[1];
				current_input.clear();
				in_break_counter = 0;
			}
		}
	}
	//map<string, string> break_state = { {"substring", "good"} };
	FSM<string, char> New_fsm = FSM<string, char>(rule_map, break_map);
	return New_fsm;
	
}

vector<string> readasvec(string filename) {
	ifstream in;
	in.open(filename);
	map<string, map<string, string>> rule_to_state;
	vector<string> input;
	{
		std::string inputString;
		while (std::getline(in, inputString)) {
			std::istringstream iss(inputString);
			std::string word;
			while (iss >> word) {
				input.push_back(word);
			}
		}
	}
	return input;
}
