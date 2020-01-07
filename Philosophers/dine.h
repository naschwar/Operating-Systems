#ifndef DINE_H
#define DINE_H
typedef enum{EATING, CHANGING, THINKING}action;
void initPhils();
void think();
void eat();
void *runPhil(void *phil);
void takeFork(int phil);
void checkFork(int phil);
void putFork(int phil);
#endif

