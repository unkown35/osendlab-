#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  int i, pid;
  int priorities[3] = {5, 10, 15};
  volatile unsigned int sum;
  unsigned int j;

  printf(1, "Parent priority changed from %d to 1\n", set_priority(getpid(), 1));
  for(i=0; i<3; i++){
    pid=fork();
    if(pid < 0){
      printf(1, "fork failed\n");
      exit();
    }
    if(pid == 0){
      // Parent will set our priority while running at priority 1.
      sum=0;
      for(j=0; j<150000000U; j++)
        sum += j & 1;
      printf(1, "Child pid %d priority %d finished (sum %d)\n",
             getpid(), priorities[i], sum);
      exit();
    }
    printf(1, "Set child %d priority %d (old %d)\n", pid,
           priorities[i], set_priority(pid, priorities[i]));
  }
  for(i=0; i<3; i++)
    wait();
  printf(1, "Done\n");
  exit();
}
