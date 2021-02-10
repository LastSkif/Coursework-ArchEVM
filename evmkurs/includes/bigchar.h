#ifndef BIGCHAR_H
#define BIGCHAR_H

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>


using namespace std;

static long int bigBC[][2] = {{2172748287, 4286677377},{2291179712, 2155905152}, {3233857791, 4278389808}, {4286611711, 4286611584}, {4286677377, 2155905152}, {16843263, 4286611711}, {16843263, 4286677503}, {541098239, 33818640}, {4286677503, 4286677377}, {4286677503, 4286611584}, {2118269952, 4342338}, {1044528640, 4080194}, {37895168, 3949058}, {1111637504, 4080194}, {2114092544, 8258050}, {33717760, 131646}, {4279769112, 404232447}, {4278190080, 255}, {1579008, 1579008}};

int bc_printA(char *str);
int bc_box(int x1, int y1, int x2, int y2);
int bc_printbigchar(long int *a, int x, int y, int simbcolor, int backcolor);
int bc_setbigcharpos(long int *BC, int x, int y, int value);
int bc_getbigcharpos(int ind, int x, int y, long int *value);
void bc_bigcharwrite(char *file, int *bigChar, int *count);
void bc_bigcharread(char *file, int *bigChar, int need_count, int *count);


#endif
