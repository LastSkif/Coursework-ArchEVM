#include "./includes/libs.h"

extern int printBCm(int pos);
extern int printflags();
extern int printmem(int position);
extern int pos;

int mt_clrscr(void){

	cout << "\E[H\E[2J";
	return 0;
}

int mt_gotoXY(int x, int y){

	cout << "\E[" << y << ";" << x << "H";
	return 0;
}

int mt_getscreensize(int *rows, int *cols){

	int width, height;
//	setvbuf(stdout, NULL, _IONBF, 0);
//	fputs("\x1B[255;255H\x1B[6n", stdout);
	scanf("\x1B[%d;%dR", &height, &width);
	*rows = height;
	*cols = width;
	return 0;
}

int mt_setfgcolor(int color){				//цвет текста  //simbol color

	cout << "\E[3" << color << "m";
	return 0;
}

int mt_setbgcolor(int color){				//цвет фона   //background color

	cout << "\E[4" << color << "m";
	return 0;
}
int drawt(int pos, int accum){
	
	mt_clrscr();
	
	        
	bc_box(63, 13, 35, 11); 	//keys box
	mt_gotoXY(65, 13);
	cout << "Keys";
	mt_gotoXY(65, 15);
	cout << "l  -  load";
	mt_gotoXY(65, 16);
	cout << "s  -  save";
	mt_gotoXY(65, 17);
	cout << "r  -  run";
	mt_gotoXY(65, 18);
	cout << "t  -  step";
	mt_gotoXY(65, 19);
	cout << "i  -  reset";
	mt_gotoXY(65, 20);
        cout << "a  -  assembler";
	mt_gotoXY(65, 21);
	cout << "F5 -  accumulator";
	mt_gotoXY(65, 22);
	cout << "F6 -  instruction Counter";

	bc_box(74, 1, 24, 2);		//accumulator box
	mt_gotoXY(82, 1);
	cout << "Accumulator";
	mt_gotoXY(86, 2);
	cout << accum;
	

	bc_box(74, 4, 24, 2);		//instruction box
	mt_gotoXY(77, 4);
	cout << "Instriction─Counter";
	mt_gotoXY(86, 5);
	cout << pos;

	bc_box(74, 7, 24, 2);		//operation box
	mt_gotoXY(82, 7);
	cout << "Operation";
	printoper();


	bc_box(74, 10, 24, 2);		//flags box
	mt_gotoXY(84, 10);
	cout << "Flags";
	mt_gotoXY(81, 11);
	printflags();

	mt_gotoXY(1, 85);
        return 0;

}

void printoper(){

	int value;
	sc_memoryGet(pos, &value);
	int comand = 0;
	int operand = 0;
	char operation[16];
	bool Flag;
	sc_regGet(wrong_command, &Flag);
	if(sc_commandDecode(value, &comand, &operand))
	{
		sprintf(operation, "+%02X:%02X", comand, operand);
	}
	else
	{
		sprintf(operation, "%04X", value);
	}
	mt_gotoXY(82, 8);
	write(1, operation, strlen(operation));
	sc_regSet(wrong_command, Flag);

}
