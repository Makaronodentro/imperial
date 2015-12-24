#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {

  char* argv[] = {NULL};

  int stat = execve("~/Mako/imperial/os/fork", argv, argv);

  int mainid = getpid();

  cout<<"Main id is: "<<mainid<<endl;
  
  int forkid = fork();
  
  int s = waitpid(forkid, 0, 0);

    cout<<"waitpid "<<s<<endl;

  if(forkid != 0)
    cout<<"X "<<getpid()<<" child of "<<getppid()<<endl;
  if(fork() != 0)
    cout<<"Y "<<getpid()<<" child of "<<getppid()<<endl;

  cout<<"Z "<<getpid()<<" child of "<<getppid()<<endl;

  return stat;
}
