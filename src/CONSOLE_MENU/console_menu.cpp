#include "console_menu.h"


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

bool output_automat_from_file(vector<string> arguments, menu* current_menu) {
	if (arguments.size() != 1) return false;
	FSM<string, char> automat = ReadFsmFromFile(arguments[0]);
	cout << " /---------------------rule of automat------------------\\" << endl;
	cout << "(-----[state from][input state] = [state to]-------------)" << endl;
	cout << " \\------------------------------------------------------/" << endl;
	automat.print_rule();
	cout << "----------------------------------------------------------" << endl;
	return true;
}
bool use_automat_from_file(vector<string> arguments, menu* current_menu){
	if (arguments.size() != 2) return false;
	FSM<string, char> automat = ReadFsmFromFile(arguments[0]);
	//automat.print_rule();
	string text = open_as_string(arguments[0]);
	string state = automat.getState(vector<char>(text.begin(), text.end()));
	std::cout << "automat is used and finite state is this: (" << state << ")" << endl;
	std::cout << "your message is: " << automat.get_break_message(state) << endl;
	return true;
	
}

state_start_menu::state_start_menu() {
	menu_information.push_back("|--------------------------<str menu>---------------------------------|");
	menu_information.push_back("|Exist one test file: --(test.txt)-- txt file.                        |");
	menu_information.push_back("|To call func print his name and argument separated by spaces         |");
	menu_information.push_back("|F - find substring in txt file with argument: filename.txt, substring|");
	menu_information.push_back("|(if there are \\t or \\n or two \" \" it'll be not working correctly)    |");
	menu_information.push_back("|O - output txt file in console with argument: filename.txt           |");
	menu_information.push_back("|E - (exit)without arguments                                          |");
	menu_information.push_back("|CHO - go to choice menu(without arguments)                           |");
	menu_information.push_back("|------------------------<end str menu>-------------------------------|");
	function_map["E"] = &exit_function;
	function_map["F"] = &isStringIn;
	function_map["O"] = &output_file;
	function_map["CHO"] = [](vector<string> arguments, menu* current_menu) -> bool {current_menu->change_menu(new choice_menu()); };
}



choice_menu::choice_menu() {
	menu_information.push_back("|------------------------<choice menu>-----------------------|");
	menu_information.push_back("|To call func print his name and argument separated by spaces|");
	menu_information.push_back("|You can choice one of next menu:                            |");
	menu_information.push_back("|E - (exit)without arguments                                 |");
	menu_information.push_back("|Str - go to(menu) finding substring(without arguments)      |");
	menu_information.push_back("|FSM - go to(menu) load fsm and test it(without arguments)   |");
	menu_information.push_back("|---------------------<end choice menu>----------------------|");
	function_map["E"] = &exit_function;
	function_map["Str"] = [](vector<string> arguments, menu* current_menu) -> bool {current_menu->change_menu(new state_start_menu()); };
	function_map["FSM"] = [](vector<string> arguments, menu* current_menu) -> bool {current_menu->change_menu(new FSM_menu()); };
}

FSM_menu::FSM_menu() {
	menu_information.push_back("|-------------------------<FSM menu>-------------------------|");
	menu_information.push_back("|To call func print his name and argument separated by spaces|");
	menu_information.push_back("|you in choice menu now. You can choice one of next menu:    |");
	menu_information.push_back("|E - (exit)without arguments                                 |");
	menu_information.push_back("|CHO - go to choice menu(without arguments)                  |");
	menu_information.push_back("|UA - use automat with arg: filename_automat, filename_text  |");
	menu_information.push_back("|OU - output fsm from file with arg: filename_automat        |");
	menu_information.push_back("|-----------------------<end FSM menu>-----------------------|");
	function_map["E"] = &exit_function;
	function_map["CHO"] = [](vector<string> arguments, menu* current_menu) -> bool {current_menu->change_menu(new choice_menu()); };
	function_map["UA"] = &use_automat_from_file;
	function_map["OU"] = &output_automat_from_file;
}

