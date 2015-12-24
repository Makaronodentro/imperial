#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

int main() {

  int forkid = fork();

  if(forkid != 0){
     cout<<"X "<<getpid()<<endl;
     int ret = waitpid(forkid, 0, 0);
  }
  if(fork() != 0){
    cout<<"Killing parent"<<getpid()<<endl;
    kill(getppid(), SIGKILL);
  }

  cout<<"Z "<<getpid()<<endl;

  return 0;
}
