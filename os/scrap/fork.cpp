#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
  if(fork() != 0)
    cout<<"Parent Code"<<endl;
  else cout<<"Child code"<<endl;

  cout<<"Common code"<<endl;

  return 0;
}
