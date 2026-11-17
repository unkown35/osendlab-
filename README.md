Name: Sai Vignan Reddy
Roll No: 2401MC44
Set: 2

Q1: Page Protection
1. Added mprotect() and munprotect() system calls.
2. Updated vm.c to change page write permissions.
3. Updated syscall files and headers for the new calls.
4. Added prottest.c to test page protection.

Q2: Priority Scheduler
1. Added priority to proc.h, defaulting to 10 in proc.c.
2. Added set_priority() system call.
3. Updated scheduler() to select the highest-priority runnable process.
4. Added schedtest.c to test scheduling with three children.
