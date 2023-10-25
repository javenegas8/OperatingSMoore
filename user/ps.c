#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  int age;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  printf("pid\tstate\t\tsize\tage\tpriority\tcputime\tppid\tname\n");
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];
    if(uproc[i].state == RUNNABLE){
    	age = uptime()-uproc[i].readytime;
    	printf("%d\t%s\t%l\t%d\t\t%d\t%d\t%d\t%s\n", uproc[i].pid, state,
                   uproc[i].size, age, uproc[i].priority, uproc[i].cputime, uproc[i].ppid, uproc[i].name);
  }
  else{
  	printf("%d\t%s\t%l\t%d\t\t%d\t%d\t%d\t%s\n", uproc[i].pid, state,
                   uproc[i].size,"", uproc[i].priority, uproc[i].cputime, uproc[i].ppid, uproc[i].name);
      }
  }

  exit(0);
}

