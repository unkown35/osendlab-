#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
  char *page;
  int pid;
  int status;

  page = sbrk(4096);
  if(page == (char*)-1){
    printf(1, "sbrk failed\n");
    exit();
  }
  page[0] = 'A';
  printf(1, "Before protection: %c\n", page[0]);

  printf(1, "mprotect: %d\n", mprotect(page, 1));
  printf(1, "Read while protected: %c\n", page[0]);
  pid = fork();
  if(pid < 0){
    printf(1, "fork failed\n");
    exit();
  }
  if(pid == 0){
    printf(1, "Child writing protected page (should be killed)...\n");
    page[0] = 'B';
    printf(1, "ERROR: child wrote protected page\n");
    exit();
  }
  status = wait();
  printf(1, "Parent reaped child %d (wait result %d)\n", pid, status);
  printf(1, "Parent still reads: %c\n", page[0]);
  printf(1, "munprotect: %d\n", munprotect(page, 1));
  page[0] = 'C';
  printf(1, "After writable again: %c\n", page[0]);
  printf(1, "Unaligned address: %d (expected -1)\n", mprotect(page+1, 1));
  printf(1, "Zero length: %d (expected -1)\n", mprotect(page, 0));
  printf(1, "Beyond process memory: %d (expected -1)\n", mprotect(page, 100000));
  exit();
}
