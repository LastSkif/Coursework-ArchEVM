#include "./includes/libs.h"

using namespace std;

int a[100];
int flags;
bool flag;
int flag_init;


int sc_memoryInit() {
	for (int i = 0; i < 100; i++) a[i] = 0;
	return 0;
}

int sc_memorySet(int address, int value) {
	if (address < 0 || address > 99){
		sc_regSet(memory_error, 1);
		return 0;
	}
		
	else
		a[address] = value;
	return 1;
}

int sc_memoryGet(int address, int *value) {
	if (address < 0 || address > 99){
		sc_regSet(memory_error, 1);
		return 0;

	}
	else
		*value = a[address];

	return 1;
}

int sc_memorySave(char* filename) {

	ofstream mem(filename, ios::binary);
	if (!mem.is_open())
	{
		cout << "Can't open file \"" << filename << "\"\n";
		return 0;
	}
	mem.write((char *)a, 100 * sizeof(int));

	return 1;
}

int sc_memoryLoad(char* filename) {

	ifstream mem(filename, ios::binary);
	if (!mem.is_open())
	{
		cout << "Can't open file \"" << filename << "\"\n";
		return 0;
	}
	mem.read((char *)a, 100 * sizeof(int));

	return 1;
}

int sc_regInit(void) { 
	flag_init = 1;
	flags = 0;
	sc_regSet(timer_ignore, true);
	return 0; 
}

int sc_regSet(int Register, bool value) {
	if(flag_init != 1) sc_regInit();

	if (value == 1){
		flags = flags | (1 << (Register - 1));
//	        cout << "reg_set1 flags = " << flags << endl;

	}
	else if (value == 0){
//		cout << "reg_set0 flags = " << flags << endl;
		flags = flags & (~(1 << (Register - 1)));
	}

	return 0;
}

int sc_regGet(int Register, bool* value) {
	if(flag_init != 1) sc_regInit();

	flag = (flags >> (Register - 1)) & 0x1;
//	cout << "reg_get flag = " << flag << endl;

	*value = flag;
	
	return 0;
}

int sc_commandEncode(int command, int operand, int* value) {
	
	if ((command < 0x10) || (command > 0x11 && command < 0x20) || (command > 0x21 && command < 0x30) || (command > 0x33 && command < 0x40) || (command > 0x43 && command < 0x51) || (command > 0x76) || (operand > 0x7f))
	{
		cout<<"Encode error\n";
		sc_regSet(encode_error, 1);
		return encode_error;
	}
	
	int code = 0x0;
	code |= command;
	code = code << 7;
	code |= operand;
	*value = code;
	return 1;
}

int sc_commandDecode(int value, int *command, int *operand) {

	if ((value & 0x4000) == 0x4000) //if 15 bit != 0
	{
		cout << "Decode error\n";
		sc_regSet(decode_error, 1);
		return decode_error;
	}
	
	int z, b;
	z = (value >> 7) & 0x7f;
	b = value & 0x7f;
	
	if ((z < 0x10) || (z > 0x11 && z < 0x20) || (z > 0x21 && z < 0x30) || (z > 0x33 && z < 0x40) || (z > 0x43 && z < 0x51) || (z > 0x76) || (b > 0x7f))
	{
		sc_regSet(decode_error, 1);
		return decode_error;
	}

	*command = z;
	*operand = b;
	return 1;
}

int printmem(int position){

	bc_box(1, 1, 72, 11);           //memory box
        mt_gotoXY(34, 1);
        cout << "Memory";


	int l = 2;
	for(int i = 0; i < 10; ++i){
		mt_gotoXY(2, l);
		for(int j = 0; j < 10; ++j){
			
			int value;
			sc_memoryGet(10 * i + j, &value);
			int command = 0;
			int opperand = 0;
			char operation[16];
			bool oldFlag;
			sc_regGet(wrong_command, &oldFlag);
			 if(i*10 + j == position){
                                mt_setbgcolor(blue);
                                mt_setfgcolor(white);
                        }
                        else{
                                mt_setbgcolor(black);
                                mt_setfgcolor(white);
                        }
			if(sc_commandDecode(value, &command, &opperand)){
				printf("+%2X:%2X ", command, opperand);
			}
			else{
				printf("+%05X ", value);
			}
			sc_regSet(wrong_command, oldFlag);
//			write(1, operation, strlen(operation));
		}
		l++;
	}

	return 0;
}

int printflags(){
	bool x;
	sc_regGet(timer_ignore, &x);
	if(x == 0)
                cout << "TE ";
        else
                cout << "TD ";

	sc_regGet(memory_error, &x);
	if(x == 0)
		cout << "0 ";
	else
		cout << "M ";
	
	sc_regGet(zero_division, &x);
        if(x == 0)
                cout << "0 ";
        else
                cout << "Z ";
	
	sc_regGet(encode_error, &x);
        if(x == 0)
                cout << "0 ";
        else
                cout << "E ";

	sc_regGet(decode_error, &x);
        if(x == 0)
                cout << "0 ";
        else
                cout << "D ";


	return 0;
}

int printBCm(int pos){
	mt_setfgcolor(white);
	mt_setbgcolor(black);
	bc_box(1, 13, 61, 11);

	int value;
	sc_memoryGet(pos, &value);
	int command = 0;
	int opperand = 0;
	char operation[16];
	bool Flag;
	sc_regGet(wrong_command, &Flag);
	if(sc_commandDecode(value, &command, &opperand)){
		sprintf(operation,"+%02X:%02X",command,opperand);
	}
	else{
		sprintf(operation,"%04X", value);
	}
	sc_regSet(wrong_command, Flag);
	int position = -6;
	for(int i = 0; i < strlen(operation); i++)
	{
		position += 9;
		switch(operation[i])
		{
			case '0':
				bc_printbigchar(bigBC[0], position, 15, red, black);
				break;
			case '1':
				bc_printbigchar(bigBC[1], position, 15, red, black);
				break;
			case '2':
				bc_printbigchar(bigBC[2], position, 15, red, black);
				break;
			case '3':
				bc_printbigchar(bigBC[3], position, 15, red, black);
				break;
			case '4':
				bc_printbigchar(bigBC[4], position, 15, red, black);
				break;
			case '5':
				bc_printbigchar(bigBC[5], position, 15, red, black);
				break;
			case '6':
				bc_printbigchar(bigBC[6], position, 15, red, black);
				break;
			case '7':
				bc_printbigchar(bigBC[7], position, 15, red, black);
				break;
			case '8':
				bc_printbigchar(bigBC[8], position, 15, red, black);
				break;
			case '9':
				bc_printbigchar(bigBC[9], position, 15, red, black);
				break;
			case 'A':
				bc_printbigchar(bigBC[10], position, 15, red, black);
				break;
			case 'B':
				bc_printbigchar(bigBC[11], position, 15, red, black);
				break;
			case 'C':
				bc_printbigchar(bigBC[12], position, 15, red, black);
				break;
			case 'D':
				bc_printbigchar(bigBC[13], position, 15, red, black);
				break;
			case 'E':
				bc_printbigchar(bigBC[14], position, 15, red, black);
				break;
			case 'F':
				bc_printbigchar(bigBC[15], position, 15, red, black);
				break;
			case '+':
				bc_printbigchar(bigBC[16], position, 15, red, black);
				break;
			case '-':
				bc_printbigchar(bigBC[17], position, 15, red, black);
				break;
			case ':':
				bc_printbigchar(bigBC[18], position, 15, red, black);
				break;
			default:
				break;
		}
	}

	mt_setbgcolor(black);
	mt_setfgcolor(white);
	printf("\E(B");
//	mt_gotoXY(1, 65);
	return 0;
}
