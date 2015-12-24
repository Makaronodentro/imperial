/******************************************************************
 * Header file for the helper functions. This file includes the
 * required header files, as well as the structures and the shared
 * memory/semaphore values (which are to be changed as needed).
 ******************************************************************/


# include <stdio.h>
# include <ctime>

# include <iostream>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/sem.h>
# include <sys/time.h>
# include <math.h>
# include <errno.h>
# include <string.h>


# define SHM_KEY 0x34 // Change this number as needed
# define SHM_W 0200
# define SHM_R 0400
# define SHM_MODE (SHM_R | SHM_W)
# define SHM_SIZE 10000 // Change this number as needed
# define SEM_KEY 0x44 // Change this number as needed

# define ITEM 0
# define SPACE 1
# define MUTEX 2

# define MAX_QUEUE_SIZE 500

using namespace std;

union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};

typedef struct jobtype
{
  int id;
  int duration;
} JOBTYPE;

typedef struct queue 
{
  int processes; // Current number of processses working on the queue
  int producers; // Number of Producers contributing to the queue
  int size; 
  int front;
  int end;
  JOBTYPE job[MAX_QUEUE_SIZE]; // Can assume this to be maximum queue size
} QUEUE;

/* Queue Helpers */
void queue_init(queue*, int);
void queue_produce(queue*, int&, int&);
void queue_consume(queue*, int&, int&);

/* Argument Helper*/
int check_arg (char *);

/* Semaphore Helpers */
int sem_create (key_t, int);
int sem_attach (key_t);
int sem_init (int, int, int);
void sem_wait (int, short unsigned int);
int sem_timewait (int, short unsigned int, int);
void sem_signal (int, short unsigned int);
int sem_close (int);

