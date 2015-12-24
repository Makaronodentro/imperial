/* -------------------------------------------------------------------------*
 * Name: consumer.cc 
 * Description: The consumer "consumes" as many jobs as it can from the queue.
 *              - Ensures proper user input.
 *              - Connects to shared memory and semaphores
 *              - Increases number of processes by 1.
 *              - While there are producers working it consumes any jobs they
 *              create one at a time. If an ITEM is not added to the queue for
 *              10 seconds it checks whether the producers have stopped. In that
 *              case it stops consuming.
 *              - Once finished it reduces the processes variable
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
   * Read in 1 cmd line arg. id of consumer
   *
   * New Variables::
   *  consumer id (cons_id)
   */

  // Ensure proper usage
  if(argc != 2){
    perror("Usage: './consumer id'");
    exit(1);
  }
  
  // Sanitize input and set cons_id
  int cons_id;
  if((cons_id = check_arg(argv[1])) == -1){
    perror("Please enter a numeric producer id");
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
   *  queue pointer (jobs) & variables
   *  execution time (t)
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
  
   // Time monitoring variables
  time_t timer1, timer2;
  int t = 0;
  
  // Initialize queue variables
  int queue_id = 0;
  int duration = 0;

  /* CONSUMER
   * ---------------------------------------------------------------------------
   * a) wait 10 seconds for an ITEM to be produced - if none stop consuming
   * b) down mutex
   * c) consume and print status
   * d) up mutex
   * e) up space
   * f) sleep(duration)
   * g) print job completion
   */

  // "Daemonize" the process
  if(fork() == 0){

    // Variable to keep track of running producers
    int producers = 0;

    // Sleep for 1 seconds to allow producers to set the producers variable
    // Must not be longer than 2 because in the case of 1 producer with 1 
    // job the consumer might quit prematurely.
    sleep(1);

    // Increase the processes variable to allow start to monitor this process
    sem_wait(semid, MUTEX);  
    jobs->processes += 1;
    producers = jobs->producers;
    sem_signal(semid, MUTEX);
    
    /* In case of multiple consumers, and few producers most consumers are
     * starved and return prematurely. To solve this issue I introduced a
     * producers variable in the shared space, that keeps track of how many
     * producers are running. If that reaches zero then the consumer is allowed
     * to quit.
     */ 
    while(producers != 0){
    
      // To reduce overhead of checking the number of producers, update it
      // only if the consumer does not receive an ITEM signal for 10 seconds.
      
      // Wait 10 seconds for an item to be freed
      if(sem_timewait(semid, ITEM, 10) != -1){
        sem_wait(semid, MUTEX); // Check for exclusive access, wait if not available
        
        queue_consume(jobs, duration, queue_id); // Consume an ITEM
        producers = jobs->producers;
        
        sem_signal(semid, MUTEX); // Signal exclusive access
        sem_signal(semid, SPACE); // Signal that a new space is available for prod
        
        // Update timer1 to exclude semaphore waiting time
        time(&timer1);
        
        // Print status
        cout<<"\e[32mConsumer("<<cons_id<<") time "<<t
            <<": Job id "<<queue_id<<" executing sleep duration "
            <<duration<<endl;
        
        // Work
        sleep(duration);
        
        // Update time
        time(&timer2);
        t += difftime(timer2, timer1);
        
        // Print job completion
        cout<<"\e[34mConsumer("<<cons_id<<") time "<<t
              <<": Job id "<<queue_id<<" completed"<<endl;
      }
      else{
        sem_wait(semid, MUTEX);  
        producers = jobs->producers;
        sem_signal(semid, MUTEX);
      }
    }
    
    // Update time
    time(&timer2);
    t += difftime(timer2, timer1);
    
    // Print status
    cout<<"\e[39mConsumer("<<cons_id<<") time "<<t
            <<": No jobs left."<<endl;
    
    // Reduce the processes variable to tell start that this consumer has finished
    sem_wait(semid, MUTEX);
    jobs->processes -= 1;
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
