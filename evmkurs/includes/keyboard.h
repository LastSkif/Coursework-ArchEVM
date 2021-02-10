#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <termios.h>
#include <sys/ioctl.h>
#include <cstring>
#include <unistd.h>


enum Keys{up, lef, down, rig, enter, f5, f6, t, i, r, l, s, ex, assemb, error};

void rk_readkey(enum Keys &key);
int rk_mytermsave(void);
int rk_mytermrestore(void);
int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint);


#endif 
