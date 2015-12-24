/******************************************************************
 * The helper file that contains the following helper functions:
 * check_arg - Checks if command line input is a number and returns it
 * sem_create - Create number of sempahores required in a semaphore array
 * sem_attach - Attach semaphore array to the program
 * sem_init - Initialise particular semaphore in semaphore array
 * sem_wait - Waits on a semaphore (akin to down ()) in the semaphore array
 * sem_timewait - Waits on a semaphore for a particular time
 * sem_signal - Signals a semaphore (akin to up ()) in the semaphore array
 * sem_close - Destroy the semaphore array
 ******************************************************************/

# include "helper.h"

// Initializes job queue
void queue_init(queue* jobs, int size){
  jobs->processes = 0;
  jobs->producers = 0;
  jobs->size = size;
  jobs->front = jobs->end = 0;
}

// Produces a job with id in the range [1, size]
void queue_produce(queue* jobs, int& duration, int& queue_id){
  // End is the index of the job to be produced
  
  // Set end equal to current end
  int end = jobs->end;
  
  // Give the new job a duration between 2 - 7
  duration = rand() % 6 + 2; // range [2,7]
  // Give it an id = end + 1
  queue_id = end + 1;
  
  // Adjust the variables in the shared memory
  jobs->job[end].id = queue_id;
  jobs->job[end].duration = duration;

  // Increase the end of the queue by 1. 
  // If it has reached the max size reset to 0.
  jobs->end = (end + 1) % jobs->size;
}

// Consumes a job
void queue_consume(queue* jobs, int& duration, int& queue_id){
  // Front is the index of the job to be consumed
  
  // Set front equal to current front
  int front = jobs->front;
  
  // Get details from shared memory
  queue_id = jobs->job[front].id;
  duration = jobs->job[front].duration;

  // Increase the front of the queue by 1. 
  // If it has reached the max size reset to 0.
  jobs->front = (front + 1) % jobs->size;
}

int check_arg (char *buffer)
{
  int i, num = 0;
  for (i=0; i < (int) strlen (buffer); i++)
  {
    if ((0+buffer[i]) > 57)
      return -1;
    num += pow (10, strlen (buffer)-i-1) * (buffer[i] - 48);
  }
  return num;
}

int sem_attach (key_t key)
{
  int id;
  if ((id = semget (key, 1,  0)) < 0)
    return -1;
  return id;
}
 
int sem_create (key_t key, int num)
{
  int id;
  if ((id = semget (key, num,  0666 | IPC_CREAT | IPC_EXCL)) < 0)
    return -1;
  return id;
}

int sem_init (int id, int num, int value)
{
  union semun semctl_arg;
  semctl_arg.val = value;
  if (semctl (id, num, SETVAL, semctl_arg) < 0)
    return -1;
  return 0;
}

// Allocate resources (wait until resource is free to allocate)
void sem_wait (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, -1, SEM_UNDO}
  };
  semop (id, op, 1);
}

int sem_timewait (int id, short unsigned int num, int tim)
{
  struct timespec ts = {tim, 0};
  struct sembuf op[] = {
    {num, -1, SEM_UNDO} // SEM_UNDO takes care of change in case of SIGKILL
  };
  if (semtimedop(id, op, 1, &ts ) == -1 )
    if (errno == EAGAIN){
      return -1;
    }
  return 0;
}

// Release resources
void sem_signal (int id, short unsigned int num)
{
  struct sembuf op[] = {
    {num, 1, SEM_UNDO}
  };
  semop (id, op, 1);
}

int sem_close (int id)
{
  if (semctl (id, 0, IPC_RMID, 0) < 0)
    return -1;
  return 0;
}
