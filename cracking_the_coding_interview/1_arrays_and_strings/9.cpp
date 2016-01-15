/* 1.9 | String Rotation
 * -----------------------------------------------------------------------------
 * Desc  : rotate a string by n positions
 *
 * Notes : Think prolog!
 */

#include <bitset>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <cctype>

using namespace std;

void rotateString(char*, char**, int);

int main(int argc, char* argv[]){

  if(argc != 3) return 1;

  char* str;

  rotateString(argv[1], &str, atoi(argv[2]));
  cout<<str<<endl;

  return 0;
}

void rotateString(char* sin, char** sout, int n){

  char* temp = new char*(strlen(sin) + 1);
  char* back = new char*((strlen(sin) + n)%strlen(sin));
  *sout = temp;

  while(sin[0]){

  }

  return;
}
