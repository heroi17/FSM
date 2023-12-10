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




int main()
{
	menu my_menu = menu();
	my_menu.start_menu_loop();


	//FSM myFSM = FSM();
	//myFSM.printMe();




	return 0;
}


