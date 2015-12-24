#include <iostream>
#include <sys/sem.h>
#include <sys/ipc.h>

using namespace std;

key_t key;
int semid;

int main() {
  
  key = ftok("/home/ubuntu/workspace/os/semaphores", 'E');
  semid = semget(key, 10, 0666 | IPC_CREAT);

  return 0;
}
