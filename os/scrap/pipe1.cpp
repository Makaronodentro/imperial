#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {
  
  int fd[2]; char buf;
  assert(argc == 2);
  if (pipe(fd) == -1) exit(1);

  if(fork() != 0) {
    close(fd[0]);
    write(fd[1], argv[1], strlen(argv[1]));
    close(fd[1]);
    waitpid(-1, NULL, 0);
  }
  else {
    close(fd[1]);
    while(read(fd[0], &buf, 1) > 0)
      cout<<buf;
    cout<<endl;
    close(fd[0]);
  }

  return 0;
}
