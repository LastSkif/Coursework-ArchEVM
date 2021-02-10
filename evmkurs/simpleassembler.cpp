#include "./includes/libs.h"

using namespace std;

int getCommand(string line, int &number)
{
	if (line.size()>11){
		auto commentIndex = line.find_first_of(";");
		line = line.substr(0,commentIndex-3);
	}
	auto index = line.find_last_of(" ");
	auto strNumber = line.substr(0,2);
	auto strCommand = line.substr(3, index - 3);
	auto strOpperand = line.substr(index + 1, 2);
	int opperand = stoi(strOpperand);
	number = stoi(strNumber);
	int command;
	if(strCommand == "="){
		return opperand;
	}
	else if(strCommand == "READ"){
		command = READ;
	}
	else if(strCommand == "WRITE"){
		command = WRITE;
	}
	else if(strCommand == "LOAD"){
		command = LOAD;
	}
	else if(strCommand == "STORE"){
		command = STORE;
	}
	else if(strCommand == "ADD"){
		command = ADD;
	}
	else if(strCommand == "SUB"){
		command = SUB;
	}
	else if(strCommand == "DIVIDE"){
		command = DIVIDE;
	}
	else if(strCommand == "MUL"){
		command = MUL;
	}
	else if(strCommand == "JUMP"){
		command = JUMP;
	}
	else if(strCommand == "JNEG"){
		command = JNEG;
	}
	else if(strCommand == "JZ"){
		command = JZ;
	}
	else if(strCommand == "HALT"){
		command = HALT;
	}
	else if(strCommand == "CHL"){
		command = CHL;
	}
	int result;
	sc_commandEncode(command, opperand, &result);
	return result;
}


void translateToBin()
{
	ifstream input("assembler.as");
	ofstream output("translated.dat", ios::binary);
	int memory[100] = {0};
	while (!input.eof())
//	for(int i = 0; i < 35; i++)
	{
		string line;
		getline(input, line);
		if(line.length() < 3)
			break;
//		cout << "a\n";
		int number;
		int code = getCommand(line, number);
		memory[number] = code;
	}

	output.write((char*)memory, 100 * sizeof(int));
	input.close();
	output.close();
}

