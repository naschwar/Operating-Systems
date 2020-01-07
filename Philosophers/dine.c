#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h> 
#include "dine.h"
#define LEFT (phil+NUM_PHILS-1)%NUM_PHILS
#define RIGHT (phil + 1)%NUM_PHILS
#define NUM_PHILS 20

sem_t mutex; //semaphore that controls the setting of a philosopher's state
sem_t forks[NUM_PHILS];
action state[NUM_PHILS];
int phils_global[NUM_PHILS];

int main(int argc, char *argv[]){
   int i;
   pthread_attr_t attr[NUM_PHILS];
   pthread_t tid[NUM_PHILS];
   /*if(argc > 1)
      numPhils = atoi(argv[1]);
   else
      numPhils = 5;*/
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


void initPhils(){
   int i;
   for(i = 0; i < NUM_PHILS; i ++){
      phils_global[i] = i;
   }
   
}

void think(){
  int i;
  int random = rand()% 100;
  for(i = 0; i < random; i ++);
}

void eat(){
   int i;
   int random = rand()% 100;
   for(i = 0; i < random; i ++);

}
void* runPhil(void *phil){
   think(); //remainder section
   takeFork(*(int*)phil);//attempt to eat, will force philosopher (process) to wait until access to eating (semaphore) is granted
   eat();//critical section
   putFork(*(int*)phil);//release access to eating (semaphore), update neighbor philosopher states
   return phil;
}



void takeFork(int phil){
	sem_wait(&mutex); //wait until given access to setting state, then lock this access from other philosopher
   state[phil] = CHANGING; 
   printf("%d  %d \n", LEFT, phil);
   checkFork(phil); //test to see if able to eat
   sem_post(&mutex); //return access to setting philosopher state
   sem_wait(&(forks[phil])); 
   /*if not granted ability to eat (semaphore was never made available), 
    * philosopher will be forced to wait (onto waiting queue of semaphore) 
    * until neighbor processes change states (give up their forks) and 
    * semaphore is updated as available*/
}


void checkFork(int phil){
   if(state[phil]== CHANGING && state[LEFT] != EATING  && state[RIGHT] !=EATING){ //only let philosopher eat if neighbors are not eating
   	state[phil] = EATING;
   	printf("EAT %d  %d \n",LEFT, phil);
   	sem_post(&(forks[phil]));//allowed to eat, wakeup whoever is waiting on forks[phil] (philosopher phil) and allow it access to eat (critical section)
   }
}

void putFork(int phil){
   sem_wait(&mutex); //wait to get access to changing state
   state[phil] = CHANGING; 
   printf("%d  %d \n", LEFT, phil);
   state[phil] = THINKING; 
   printf("THINK %d  %d\n", LEFT, phil);
   checkFork(LEFT); //update neighbor states to potentially eat if already waiting on their semaphores to access critical section
   checkFork(RIGHT);
   sem_post(&mutex);//release control of setting state
}
