// read a file into memory
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;

int main () {
  int *ip;      // Integer pointer
  int a[10];    // Integer array
  ip = &a[0];
  *ip = 1;
  ip = &a[3];   // *ip == a[3]
  int* ip2 = ip + 1; // *ip2 == a[4]
  *ip2 = 4;     // a[4] = 4
  
  for(int i = 0; i < 5; i++){
      cout<<a[i]<<endl;
  }

  return 0;
}