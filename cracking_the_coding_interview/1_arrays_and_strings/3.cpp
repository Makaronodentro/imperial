/* 1.3 | URLify
 * -----------------------------------------------------------------------------
 * Desc  : replace all spaces with "%20"
 *
 * Notes : O(N) (2 pass)
 *         Because you want to change the pointer and not its contents you have
 *         to pass a pointer to a pointer
 */

#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

void URLify(char*, char**);

int main(int argc, char* argv[]){

  // Single pointer
  char* str;

  // Pass the single pointer's address to the function
    // The function will change the pointer's address
  URLify(argv[1], &str);
  if(str){
    cout<<str<<endl;
  }

  return 0;
}

void URLify(char* sin, char** sout){

  char* pass1;
  pass1 = sin;

  int spaces = 0;

  while(pass1[0]){
      if(pass1[0] == ' ') spaces++;
      pass1++;
  }

  char* temp = new char[strlen(sin)+spaces*3+1];

  *sout = temp;

  while(sin[0]){
    if(sin[0] == ' '){
      temp[0] = '%';
      temp++;
      temp[0] = '2';
      temp++;
      temp[0] = '0';
      temp++;
    }
    else{
      temp[0] = sin[0];
      temp++;
    }

    sin++;
  }

  temp[0] = '\0';
}
