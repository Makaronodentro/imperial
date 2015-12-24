/* -------------------------------------------------------------------------*
 * Name: producer.cc 
 * Description: The producer creates the specified number of jobs.
 *              - Ensures proper user input.
 *              - Connects to shared memory and semaphores
 *              - Increases number of processes and producers by 1.
 *              - Produces n jobs, and avoids non-deterministic 
 *              results using semaphores.
 *              - Once finished it reduces the processes and producers variables
 *              and becomes dormant periodically checking whether all the other 
 *              processes have finished executing and does not return until they
 *              have done so.
 *
 * Author: Georgios Kontogiannis, gk513@ic.ac.uk
 * Last Updated: 10th December 2015
 * 
 * Comments: ASCII color code has been used to make output more user friendly. 
 *           Please remove it from lines 130, 143 if it causes issues.
 *
 * -------------------------------------------------------------------------*/

# include "helper.h"

int main (int argc, char *argv[])
{
  /* COMMAND LINE INPUT
   * ---------------------------------------------------------------------------
   * Read in 2 cmd line args - id of producer and jobs to generate
   *
   * New Variables::
   *  producer id (prod_id)
   *  number of jobs (no_jobs)
   */
   
  // Ensure proper usage
  if(argc != 3){
    perror("Usage: './producer id no_jobs'");
    exit(1);
  }
  
  int prod_id;
  // Sanitize input
  if((prod_id = check_arg(argv[1])) == -1){
    perror("Please enter a numeric producer id");
    exit(1);
  }
  
  int no_jobs = check_arg(argv[2]);
  if(no_jobs < 1){
    perror("Please ensure the number of jobs is greater than 1.");
    exit(1);
  }
  
  
  /* SHARED MEMORY, SEMAPHORE, JOB QUEUE CREATION and TIME MONITORING 
   * ---------------------------------------------------------------------------
   * - Associate queue with the shared memory segment, if available, else create
   * - Attach semaphore
   * - Initialize queue size
   * - Declare time monitoring variables
   *
   * New Variables::
   *  shared memory id (shmid)
   *  semaphore id (semid)
   *  queue pointer (jobs) and variables
   *  (t) total running time in seconds.
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

  // Attach semaphore
  int semid = sem_attach(SEM_KEY);
  
  // Initialize jobs queue size, front and end
  int duration = 0;
  int job_id = 0;
  
  // Time monitoring variables.
  time_t timer1, timer2; 
  int t = 0;
  
  /* PRODUCER
   * ---------------------------------------------------------------------------
   * a) down space
   * b) down mutex
   * c) produce and print status
   * d) up mutex
   * e) up item
   * f) sleep [2,4]
   */
  
  // "Daemonize the process"
  if(fork() == 0){
   
    // Increase the processes and producers variables to allow other processes
    // to monitor this process' use of semaphores
    sem_wait(semid, MUTEX);  
    jobs->processes += 1;
    jobs->producers += 1;
    sem_signal(semid, MUTEX);
    
    // For the number of jobs provided produce and print status
    for(int i = 0; i < no_jobs; i++){
      
      sem_wait(semid, SPACE); // Check for empty space in the queue, wait if full
      sem_wait(semid, MUTEX); // Check for exclusive access, wait if not available
      
      queue_produce(jobs, duration, job_id); // Produce an ITEM
  
      sem_signal(semid, MUTEX); // Signal that exclusive access is now available
      sem_signal(semid, ITEM); // Signal that a new item is available for cons
      
      // Update timer1 to exclude semaphore waiting time
      time(&timer1);
      
      // Print status
      cout<<"\e[39mProducer("<<prod_id<<") time "<<t
            <<": Job id "<<job_id<<" duration "
            <<duration<<endl;
      
      // Sleep for 2 - 4 seconds
      sleep(rand() % 3 + 2); // range [2, 4]
      
      // Update time
      time(&timer2);
      t += difftime(timer2, timer1);
    }
    
    // Output status
    cout<<"\e[39mProducer("<<prod_id<<") time "<<t
            <<": No more jobs to generate."<<endl;
    
    // Reduce the processes variable to tell start that this producer has finished
    sem_wait(semid, MUTEX);
    jobs->processes -= 1;
    jobs->producers -= 1;
    sem_signal(semid, MUTEX);
    
    // Monitor whether all other processes have finished before returning
    // Prevents semaphores from malfunctioning
    int p;
    while(1){
      
      // Update number of running processes
      sem_wait(semid, MUTEX);
      p = jobs->processes;
      sem_signal(semid, MUTEX);
      
      // If no more processes left break and return
      if(p == 0)
        break;
      
      // To reduce the number of times it intercepts the MUTEX signal
      // 7 to allow other consumers to consume at least 1 before rechecking
      sleep(7);
    }
  }
  
  return 0;
}
