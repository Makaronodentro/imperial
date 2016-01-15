/* 1.6 | String Compression
 * -----------------------------------------------------------------------------
 * Desc  : compress string by counting repeated chars.
 *         If the "compressed" string is longer, return the original
 *         Compress up to 9 chars in a row
 *
 * Notes : Avoid multiple concatenations as they are inefficient.
 */

#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

int finalLength(char*);
void compString(char*, char**);

int main(int argc, char* argv[]){

  char* str;

  compString(argv[1], &str);

  cout<<str<<endl;

  delete str;

  return 0;
}

void compString(char* sin, char** sout){
  int compressedLength = finalLength(sin);

  if(compressedLength >= strlen(sin)) *sout = sin;

  char* temp = new char[compressedLength + 1];

  *sout = temp;
  char curr = sin[0]; // current char
  int count = 0; // current char count

  while(sin[0]){
    if(sin[0] == curr){
      count++;
    }
    else{
      temp[0] = curr;
      cout<<"Current count "<<count<<endl;
      temp[1] = '0' + (count % 9);

      curr = sin[0];
      count = 1;

      temp += 2;
    }

    sin++;
  }
}

int finalLength(char* str){
  int length = 0;
  char curr = str[0];

  while(str[0]){
    if(str[0] != curr) length += 2;
    str++;
  }

  return length;
}
