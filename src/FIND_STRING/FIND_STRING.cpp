#include "FIND_STRING.h"




bool IsStringIn(string text, string substring, string alphabet) {
	FSM<string, char> Fsm_finder_string = generateAutomatStrIn(substring, alphabet);
	string state = Fsm_finder_string.getState(vector<char>(text.begin(), text.end()));//optimisation is bad becouse i didn't think about the design
	//Fsm_finder_string.print_rule();
	return (state == substring);
}



FSM<string, char> generateAutomatStrIn(string substring, string alphabet) {


	map<string, map<char, string>> find_string_map;
	//set "" state
	{
		string current_state = "";
		for (int j = 0; j < alphabet.size(); j++) {
			find_string_map[current_state][alphabet[j]] = "";
		}
		for (int i = 0; i < substring.size(); i++) {
			current_state += substring[i];
			for (int j = 0; j < alphabet.size(); j++) {
				find_string_map[current_state][alphabet[j]] = "";
			}
		}
	}
	//set rule to change state
	{
		string current_state = "";
		find_string_map[""][substring[0]] = substring[0];//переход из "" в первый символ строки


		for (int i = 0; i < substring.size(); i++) {
			current_state += substring[i];
			for (int j = 0; j < alphabet.size(); j++) {
				//set zero state, when zero simbols
				string finder_state = current_state;
				finder_state += alphabet[j];
				while (finder_state != "") {
					if (find_string_map.find(finder_state) != find_string_map.end()) {
						find_string_map[current_state][alphabet[j]] = finder_state;
						break;
					}
					finder_state.erase(0, 1);
				}
			}
		}
	}
	map<string, string> break_state = { {substring, "good"} };
	FSM New_fsm = FSM<string, char>(find_string_map, break_state);
	return New_fsm;

}