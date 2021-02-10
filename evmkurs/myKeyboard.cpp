#include "./includes/libs.h"

using namespace std;

void rk_readkey(enum Keys &key){
	char buf[8];
	bool ignore;
	sc_regGet(timer_ignore, &ignore);

	if(!ignore && key != r){
//                key = error;
                return;
        }


	if(read(1, buf, 7) > 0){
		if(strncmp(buf, "\033[A", 3) == 0) key = up;	
		else if(strncmp(buf, "\033[B", 3) == 0) key = down;
		else if(strncmp(buf, "\033[C", 3) == 0) key = rig;
		else if(strncmp(buf, "\033[D", 3) == 0) key = lef;
		else if(strncmp(buf, "\n", 1) == 0) key = enter;
		else if(strncmp(buf, "\033[15~", 5) == 0) key = f5;
		else if(strncmp(buf, "\033[17~", 5) == 0) key = f6;
		else if(strncmp(buf, "t", 1) == 0) key = t;
		else if(strncmp(buf, "i", 1) == 0) key = i;
		else if(strncmp(buf, "r", 1) == 0) key = r;
		else if(strncmp(buf, "l", 1) == 0) key = l;
		else if(strncmp(buf, "s", 1) == 0) key = s;
		else if(strncmp(buf, "q", 1) == 0) key = ex;
		else if(strncmp(buf, "a", 1) == 0) key = assemb;
		else key = error;
	}
	
}


int rk_mytermsave(void){
	struct termios terminal;
	FILE * term;
	if(tcgetattr(0, &terminal) != 0){
		return -1;
	}
	if((term = fopen("term", "wb")) == NULL){
		return -1;
	}
	fwrite(&terminal, sizeof(terminal), 1, term);
	fclose(term);
	return 0;
}

int rk_mytermrestore (void){
	struct termios terminal;
	FILE * term;
	if((term = fopen("term", "wb")) == NULL){
		return -1;
	}
	if(fread(&terminal, sizeof(terminal), 1, term) > 0){
		if(tcsetattr(0, TCSAFLUSH, &terminal) != 0){
			return -1;
		}
		else{
			fclose(term);
		}
	}
	return 0;
}

int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint){
	termios rawMode;
	if(tcgetattr(0, &rawMode) != 0) return -1;

	if(regime == 1) rawMode.c_lflag |=ICANON;		// флаг канонического режима; 1 - вкл, 0 - выкл
								// 0 1 1 0 1 - для стрелочек 
	else if(regime == 0) rawMode.c_lflag &=~ICANON;
	if(echo == 1) rawMode.c_lflag |=ECHO;			// флаг отображения символов
	else if(echo == 0) rawMode.c_lflag &=~ECHO;
	if(sigint == 1) rawMode.c_lflag |=ISIG;			// флаг обработки клавиш прерывания и авар. завершения
	else if(sigint == 0) rawMode.c_lflag &=~ISIG;		//
	rawMode.c_cc[VTIME] = vtime;
	rawMode.c_cc[VMIN] = vmin;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &rawMode);
	return 1;
}






