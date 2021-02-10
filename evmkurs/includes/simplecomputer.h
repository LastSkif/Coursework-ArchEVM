#ifndef SIMPLECOMPUTER_H
#define SIMPLECOMPUTER_H

#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define memory_error 0
#define wrong_command 1
#define zero_division 2
#define encode_error 3
#define decode_error 4
#define timer_ignore 5


int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char* filename);
int sc_memoryLoad(char* filename);
int sc_regInit(void);
int sc_regSet(int register, bool value);
int sc_regGet(int register, bool *value);
int sc_commandEncode(int command, int operand, int* value);
int sc_commandDecode(int value, int* command, int* operand);
int printmem(int position);
int printflags();
int printBCm(int pos);

#endif
