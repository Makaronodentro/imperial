/* -------------------------------------------------------------------------*
 * Name: start.cc
 * Description: The start program enables and coordinates the collboration
 *              of the producers and consumers. It has 3 main functions.
 *              a) Create and initialise the Semaphores
 *              b) Create the shared memory and initialise the shared variables
 *              c) Periodically monitor whether the producers and consumers are
 *              still working and cleanup the semaphores and shared memory once
 *              all the producers and consumers have stopped working.
 *
 * Author: Georgios Kontogiannis, gk513@ic.ac.uk
 * Last Updated: 10th December 2015
 * 
 * Comments: fork() has been used to place the process in the background.
 *
 * -------------------------------------------------------------------------*/

# include "helper.h"

int main (int argc, char **argv)
{
  /* COMMAND LINE INPUT
   * ---------------------------------------------------------------------------
   * Read in 1 cmd line arg - id of producer and jobs to generate
   *
   * New Variables::
   *  job queue size (queue_size)
   */

  // Check for correct number of arguments (1 argument)
  if(argc != 2){
    perror("Usage: './start queue_size'");
    exit(1);
  }
  
  // Ensure the queue size is 
  int queue_size = check_arg(argv[1]);
  if(queue_size < 1 || queue_size > MAX_QUEUE_SIZE){
    perror("Please provide a queue size within the range [1,500]");
    exit(2);
  }
  
   /* SEMAPHORES
   * ---------------------------------------------------------------------------
   * Create and initialise the semaphore array
   *
   * New Variables::
   *  semaphore id (semid)
   */
  
  // Create the semaphores
  int semid;
  if((semid = sem_create(SEM_KEY, 3)) == -1){
    perror("Error creating semaphores");
    exit(3);
  }
  
  // Init semaphores
  
  // Number of items already in the queue (initially 0)
  if(sem_init(semid, ITEM, 0) == -1){
    perror("Error initiating item semaphore");
    exit(3);
  }
  // Empty space in the queue (initially = queue size)
  if(sem_init(semid, SPACE, queue_size) == -1){
    perror("Error initiating space semaphore");
    exit(3);
  }
  // Binary semaphore
  if(sem_init(semid, MUTEX, 1) == -1){
    perror("Error initiating mutex semaphore");
    exit(3);
  }
  
  /* SHARED MEMORY AND QUEUE INITIALISATION
   * ---------------------------------------------------------------------------
   * Create shared memory space and initialise the job queue
   *
   * New Variables::
   *  shared memory id (shmid)
   *  job queue pointer(jobs)
   */
  
  int shmid;
  queue* jobs;
  
  // Connect or create the shm
  if((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE | IPC_CREAT)) == -1){
    perror("shmget");
    exit(2);
  }
  
  // Assign the jobs pointer to the segment
  jobs = (queue*)shmat(shmid, (void *)0, 0);
  if(jobs == (queue*)(-1)){
    perror("shmat");
    exit(3);
  }
  
  // Call the queue initializer
  queue_init(jobs, queue_size);
  
  /* CLEANUP
   * ---------------------------------------------------------------------------
   * Monitor other processes and wait for them to finish
   * Once done delete shared memory and semaphores
   *
   * New Variables::
   *  number of outstanding processes (p)
   */
  
  // Fork a new process to put start in the background
  if(fork() == 0){
    
    // Wait 20 seconds for other processes to start executing
    sleep(20);
    
    int p;
    while(1){
      
      // Update number of processes
      sem_wait(semid, MUTEX);
      p = jobs->processes;
      sem_signal(semid, MUTEX);
      
      // If 0 processes are running stop monitoring
      if(p == 0)
        break;
      
      /* Sleep to reduce the number of times it intercepts the MUTEX signal
       * 14 to allow all other waiting processes to terminate themselves before
       * Checking again
       */
      sleep(14);
    }
    
    // before quitting delete shared memory and semaphores 

    // Detach shm
    if(shmdt(jobs) == -1){
      perror("shmdt");
      exit(4);
    }
  
    // Delete the shm segment
    shmctl(shmid, IPC_RMID, NULL);
    
    // close semaphore array
    sem_close(semid);
  }
  
  return 0;
}
