#include "./includes/libs.h"

int pos, accum;

int main(){
	
	int e, com, oper;
	enum Keys a;
	pos = 0;
	accum = 0;
	static struct itimerval newTime, oldTime;
	newTime.it_interval.tv_sec=1;
	newTime.it_interval.tv_usec=0;
	newTime.it_value.tv_sec=1;
	newTime.it_value.tv_usec=0;
	signal(SIGALRM, handle);
	setitimer(ITIMER_REAL, &newTime, &oldTime);
	
	while(1){
		rk_mytermregime(0, 1, 1, 0, 1);

		fflush(stdin);
		fflush(stdout);
		drawt(pos, accum);
		printmem(pos);

		fflush(stdin);
                fflush(stdout);
		
		printBCm(pos);
		printBCm(pos);
		
		mt_gotoXY(1, 65);
		rk_readkey(a);
		if(a == up) pos -= 10;
		else if(a == down) pos += 10;
		else if(a == rig) pos += 1;
		else if(a == lef) pos -= 1;
		else if(a == f5){
			rk_mytermregime(1, 1, 1, 1, 1);
			mt_gotoXY(1, 65);
			cout << "Print your value: ";
			cin >> accum;	
		}
		else if(a == f6){

			rk_mytermregime(1, 1, 1, 1, 1);
//			mt_getscreensize(&row, &col);
                        mt_gotoXY(1, 65);
                        cout << "Print your value: ";                
			cin >> pos;
			
		}
		else if(a == s){
//			rk_mytermsave();
			sc_memorySave("memory.dat");
		}
		else if(a == l){
			sc_memoryLoad("memory.dat");
//			rk_mytermrestore();
		}
		else if(a == r){
			run();
		}
		else if(a == t){
			step();
		}
		else if(a == ex){
			mt_clrscr();
			rk_mytermregime(1, 1, 1, 1, 1);
			break;
		}
		else if(a == i){
			sc_memoryInit();
			sc_regInit();
			pos = 0;
			accum = 0;
			sc_regSet(timer_ignore, true);
		}
		else if(a == enter){
			int value;
			rk_mytermregime(1, 1, 1, 1, 1);
			mt_gotoXY(1, 65);
			cout << "Print your command: ";
			cin >> hex >> com;
			cout << "Print your operand: ";
			cin >> hex >> oper;
			if(sc_commandEncode(com, oper, &value) == 1)
				sc_memorySet(pos, value);
			else
				cout << "Error: wrong command or operand\n";
		}
		else if(a == assemb){
			translateToBin();
			sc_memoryLoad("translated.dat");
		}
		else if(a == error){
			continue;                   		
		}
		if(pos < 0) pos += 100;
		else if(pos > 99) pos %= 100;
		
	}

	return 0;
}
