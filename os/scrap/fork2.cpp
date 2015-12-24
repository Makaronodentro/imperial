#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  if(fork() != 0)
    cout<<"X "<<getpid()<<endl;
  if(fork() != 0)
    cout<<"Y "<<getpid()<<endl;

  cout<<"Z "<<getpid()<<endl;

  return 0;
}
