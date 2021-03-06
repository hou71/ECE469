#include "usertraps.h"
#include "misc.h"

int rec(int n)
{
  if(n == 0) {return 0;}
  // recursion to grow the call stack
  return (1 + rec(n - 1));
}

void main (int argc, char *argv[])
{
  sem_t s_procs_completed; // Semaphore to signal the original process that we're done
  int x = 2500;
  int out;

  if (argc != 2) { 
    Printf("Usage: %s <handle_to_procs_completed_semaphore>\n"); 
    Exit();
  } 

  // Convert the command-line strings into integers for use as handles
  s_procs_completed = dstrtol(argv[1], NULL, 10);

  // Now print a message to show that everything worked
  Printf("part4 (%d): Testing growing stack past 1 page!\n", getpid());

  // call recursive function to grow the call stack
  out = rec(x);

  // Signal the semaphore to tell the original process that we're done
  if(sem_signal(s_procs_completed) != SYNC_SUCCESS) {
    Printf("part4 (%d): Bad semaphore s_procs_completed (%d)!\n", getpid(), s_procs_completed);
    Exit();
  }

  Printf("part4 (%d): Done!\n", getpid());
}
