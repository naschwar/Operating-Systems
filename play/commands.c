#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alloc.h"

void RLcommand(char **command, Process **mem, Process **processes, int numProcs){
    printf("made it to RL\n");
    printf("size: %s\n",command[1]);
    for(int i = 0; i < numProcs; i ++){
       if(processes[i] != NULL){
          if((processes[i])->name

}

void Ccommand(Process **mem, Process **processes, long size){
    
    printf("made it to C\n");
    long count = 0;
    long memLoc = 0;
    long temp = 0;
    Process *proc;
    while(memLoc < size){
       while(processes[memLoc] == NULL){
          count ++;
          memLoc ++;
          if(!(memLoc < size))
             return;
       }
       proc = mem[memLoc];
       temp = (proc -> end) - (proc ->begin);
       proc -> begin -=count;
       proc -> end -= count;
		 mem[memLock - count] = proc;
		 mem[memLoc] = NULL;
		 mem[memLock + temp - count] = proc;  
		 mem[memLock + temp] = NULL;
		 count = 0;
    }
}

void STATcommand(Process **mem, Process **processes, long size){
    printf("made it to STAT\n");
    long memLoc = 0;
    long tempStart = 0;
    while(memLoc < size){
       printf("Addresses ");
       if(mem[memLoc] != NULL){
          printf("[%ld:%ld] Process %s\n", mem[memLoc]->begin, mem[memLoc]->end, mem[memLoc]->name);
          memLoc = ((mem[memLoc]) -> end) + 1;
       }else{
          tempStart = memLoc;
          while((memLoc < size) && (mem[memLoc] ==NULL)){
             memLoc ++;
          }
          printf("[%ld:%ld] Unused", tempStart, memLoc-1);
       }
   }
}

void EXITcommand(char **args, Process **mem, Process **processes){
   int i =0; 
	
    while(args[i]!=NULL){
        free(args[i]);
        i++;
    }
    /*need to free mem and processes here properly*/
    free(args);
    free(mem);
}
