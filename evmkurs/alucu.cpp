#include "./includes/libs.h"

using namespace std;
extern int pos;
extern int accum;
extern int a[];

int alu(int com, int oper)
{
	int result = 1;
	int value = 0;
	switch(com){
		case ADD:
		{
			result = sc_memoryGet(oper, &value);
			accum += value;
			break;
		}
		case SUB:{
			result = sc_memoryGet(oper, &value);
			accum -= value;
			break;
		}
		case DIVIDE:{
			result = sc_memoryGet(oper, &value);
			if(value != 0){
				accum /= value;
			}
			else{
				sc_regSet(zero_division, 1);
			}
			break;
		}
		case MUL:
		{
			result = sc_memoryGet(oper, &value);
			accum *= value;
			break;
		}
		default:
			result = 0;
			break;
	}
	return result;
}


void cu(){
	int com, oper;
	if(!getCommandOper(pos, &com, &oper)){
		return;
	}
	rk_mytermregime(1, 1, 1, 1, 1);
	switch(com)
	{
		case READ:
		{
			mt_gotoXY(1, 65);
			cout<<"Input: ";
			int input;
			cin >> hex >> input;
			sc_memorySet(oper, input);
			break;
		}
		case LOAD:
		{
			int value;
			sc_memoryGet(oper, &value);
			accum = value;
			break;
		}
		case WRITE:
		{
			int value;
			sc_memoryGet(oper, &value);
			mt_gotoXY(1, 65);
			cout << "RESULT = " << value << endl;
			sleep(5);
			break;
		}
		case STORE:
		{
			sc_memorySet(oper, accum);
			break;
		}
		case JUMP:
		{
			pos = oper - 1;
			break;
		}
		case JNEG:
		{
			if(accum < 0)
				pos = oper - 1;
			break;
		}
		case JZ:
		{
			if(accum == 0)
				pos = oper - 1;
			break;
		}
		case HALT:
		{
			sc_regSet(timer_ignore, true);
			pos = pos - 1;
			break;
		}
		case CHL:
		{
			int value;
			sc_memoryGet(oper, &value);
			accum = value << 1;
			break;
		}
		case ADD:
		{
			alu(com, oper);
			break;
		}
		case SUB:
		{
			alu(com, oper);
			break;
		}
		case DIVIDE:
		{
			alu(com, oper);
			break;
		}
		case MUL:
		{
			alu(com, oper);
			break;
		}
		default:
			break;
	}
	rk_mytermregime(0, 1, 1, 0, 1);
}

int getCommandOper(int position, int *comm, int *oper){
	if (sc_memoryGet(position, comm)){

		if(!sc_commandDecode(a[position], comm, oper)){

			sc_regSet(timer_ignore, true);
		}
		return 1;
	}
	else{
		sc_regSet(timer_ignore, true);
	}
	return 0;
}

