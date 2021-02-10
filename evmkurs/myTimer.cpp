#include "./includes/libs.h"

extern int pos;
extern int accum;
bool runing = false;

void step(){

	runing = true;
	cu();
	pos++;
	if(pos > 99) pos = 0;
	runing = false;

}	
	
void run(){

	signal(SIGUSR1,handle);
	raise(SIGUSR1);

}

void handle(int sgnl){

	bool ignore;
	sc_regGet(timer_ignore, &ignore);
	if(sgnl == SIGUSR1)
	{
		sc_regSet(timer_ignore, !ignore);
	}
	if(!ignore)
	{
		step();

		fflush(stdin);
                fflush(stdout);
                drawt(pos, accum);
                printmem(pos);
                printBCm(pos);
                printBCm(pos);
	}
}
