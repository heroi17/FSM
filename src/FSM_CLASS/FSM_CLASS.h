#pragma once
#include <sstream>

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
template<class state, class input>
class FSM {
public:
	FSM(map<state, map<input, state>> rule_to_state, map<state, string> break_state) : rule_to_state(rule_to_state), break_state(break_state) {};
	state getState(vector<input> text) {
		current_state = base_state;
		for (const char& c : text) {
			current_state = rule_to_state[current_state][c];
			if (break_state.find(current_state) != break_state.end()) return current_state;
		}
		return current_state;
	}
	void setCurrenState(state state) {
		current_state = state;
	}
	//debug func
	void printMe() {
		cout << "FSM is exist" << endl;
	}
	void print_rule() {
		for (const auto& [k, v] : rule_to_state)
			for (const auto& [k1, v1] : v)
				std::cout << "[" << k << "][" << k1 << "]: (" << v1 << ") " << std::endl;

	}
	string get_break_message(state current_state) {
		if (break_state.find(current_state) == break_state.end()) return "it's not finite(break) state";
		return break_state[current_state];
	}
private:
	state base_state = "";
	state current_state = "";
	map<state, map<input, state>> rule_to_state;
	map<state, string> break_state;

};


FSM<string, char> ReadFsmFromFile(string filename);
vector<string> readasvec(string filename);