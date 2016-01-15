#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

void alternate(char* s1, char* s2, char** sout);

int main(int argc, char* argv[]){

  char* str;

  alternate(argv[1], argv[2], &str);

  cout<<str<<endl;

  delete str;

  return 0;
}

void alternate(char* s1, char* s2, char** sout){
  char* temp = new char[strlen(s1) + strlen(s2) + 1];
  *sout = temp;

  while(s1[0]){
    temp[0] = s1[0];
    temp++;
    s1++;
    if(s2[0]){
      temp[0] = s2[0];
      temp++;
      s2++;
    }
  }
}
