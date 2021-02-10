#ifndef TIMER_H
#define TIMER_H

#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std;

void step();
void run();
void handle(int sgnl);

#endif
