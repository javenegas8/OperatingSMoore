#include "types.h"
#include "riscv.h"
#include "param.h"
#include "defs.h"
#include "spinlock.h"

#define NSEM 100

struct semtab semtable;
void seminit(void)
{
	initlock(&semtable.lock, "semtable");
	for (int i = 0; i < NSEM; i++)
	initlock(&semtable.sem[i].lock, "sem");
};

//find semaphore index to use
int semalloc(void){
	acquire(&semtable.lock);
	for (int i = 0; i < NSEM; i++){
		//valid means its not empty
		if(!semtable.sem[i].valid){
			//planning to use this semaphore
			semtable.sem[i].valid = 1;
			release(&semtable.lock);
			return i;
		}
	}
	release(&semtable.lock);
	return -1;
};

//invalidate entry of given index
void sedealloc(int index){
	acquire(&semtable.sem[index].lock);
	//make sure index arg is valid
	if(index > -1 && index < NSEM){
		//invalidate the entry
		semtable.sem[index].valid = 0;
	}
	release(&semtable.sem[index].lock);
};
