#ifndef TERMINAL_H
#define TERMINAL_H

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

#define black 0
#define red 1
#define green 2
#define brown 3
#define blue 4
#define purple 5
#define ocean 6
#define white 7



using namespace std;

int mt_clrscr(void);
int mt_gotoXY(int x, int y);
int mt_getscreensize(int *rows, int *cols);
int mt_setfgcolor(int colorsf);
int mt_setbgcolor(int colors);
int drawt(int ps, int ac);
void printoper();

#endif
