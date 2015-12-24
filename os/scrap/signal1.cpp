#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

void my_handler(int sig){
  cout<<"Ignoring SIGINT ..."<<endl;
}

int main() {
  
  int a = 0;

  cout<<"Pid: "<<getpid()<<endl;

  signal(SIGINT, my_handler);

  while(a != 1){
    cin>>a;
  }

  return 0;
}
