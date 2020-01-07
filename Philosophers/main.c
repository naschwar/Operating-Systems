#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "dine.h"
/*extern sem_t mutex; //semaphore that controls the setting of a philosopher's state
extern int NUM_PHILS;
extern sem_t forks[NUM_PHILS];
extern enum{ EATING, CHANGING, THINKING} state[NUM_PHILS];
extern int phils_global[NUM_PHILS];
*/
int main(int argc, char *argv[]){
   int i;
   sem_t mutex; //semaphore that controls the setting of a philosopher's state
   int NUM_PHILS;
   sem_t forks[NUM_PHILS];/*each philosopher is given a corresponding semaphore
										which will control its access to eaching; can be though
										of as the necessary forks for a philosopher to each, not
										a single fork, but the set of forks that when attained 
										will prevent or delay a philospher from eating */ 
   enum{ EATING, CHANGING, THINKING} state[NUM_PHIL];
   int phils_global[NUM_PHILS];


   pthread_attr_t attr[NUM_PHILS];
   pthread_t tid[NUM_PHILS];
   if(argc > 1)
      NUM_PHILS = atoi(argv[1]);
   else
      NUM_PHILS = 5;
   initPhils();
   sem_init(&mutex, 0,1);
   for(i = 0; i < NUM_PHILS; i ++)
      sem_init(&(forks[i]), 0, 1);
   for(i = 0; i < NUM_PHILS; i ++){
      pthread_attr_init(&(attr[i]));
      pthread_create(&(tid[i]), &(attr[i]), &runPhil, &(phils_global[i]));
   }
   for(i = 0; i< NUM_PHILS; i ++){
      pthread_join(tid[i], NULL);
   }
   exit(0);
}

/*void initPhils(){
   int i;
   phils_global = (int*)malloc(NUM_PHILS * sizeof(int));
   for(i = 0; i < NUM_PHILS; i ++)
      phils_global[i] = i;
   }
}

void think(){
  int i =0;
  int random = rand()% 100;
  while(i < random)
     i ++;
}

void eat(){
  int i =0;
  int random = rand()% 100;
  while(i < random)
     i ++;
}
void* runPhil(void *phil){
   int left = phil;
   int right  = (phil + 1) %NUM_PHILS;
   think() //remainder section
   takeFork(*phil, right, left);//attempt to eat, will force philosopher (process) to wait until access to eating (semaphore) is granted
   eat();//critical section
   putFork(*phil, right, left);//release access to eating (semaphore), update neighbor philosopher states
}



void takeFork(int phil, int right, int left){
	sem_wait(&mutex); //wait until given access to setting state, then lock this access from other philosopher
   state[phil] = CHANGING; 
   printf("\n");
   check_fork(phil, right, left); //test to see if able to eat
   sem_post(&mutex); //return access to setting philosopher state
   sem_wait(&forks[phil]); //if not granted ability to eat (semaphore was never made available), philosopher will be forced to wait (onto waiting queue of semaphore) until neighbor processes change states (give up their forks) and semaphore is updated as available
}


void checkFork(int phil, int right, int left){
   if(state[i] == CHANGING && state[left] != EATING  && state[right] !=EATING){ //only let philosopher eat if neighbors are not eating
   	state[phil] = EATING;
   	printf("EAT\n");
   	sem_post(&(forks[phil]));//allowed to eat, wakeup whoever is waiting on forks[phil] (philosopher phil) and allow it access to eat (critical section)
   }
}

void putFork(int phil, int right, int left){
   sem_wait(&mutex); //wait to get access to changing state
   state[phil] = CHANGING; 
   printf("\n");
   state[phil] = THINKING; 
   printf("THINK\n");
   checkFork(left); //update neighbor states to potentially eat if already waiting on their semaphores to access critical section
   checkFork(right);
   sem_post(&mutex);//release control of setting state
}*/
