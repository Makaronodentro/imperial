/* 1.4 | Palindrome Permutation
 * -----------------------------------------------------------------------------
 * Desc  : Check if string is a permutation of a palindrome
 *
 * Notes : make sure that only 1 or 0 characters occur odd times
 */

#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

bool isPalindrome(const char*);

int main(int argc, char* argv[]){

  if(isPalindrome(argv[1])) cout<<"True"<<endl;
  else cout<<"False"<<endl;

  return 0;
}

bool isPalindrome(const char* str){

  bitset<128> ch;

  while(str[0]){
    ch.flip(str[0]);
    str++;
  }

  if(ch.count() > 1)return false;
  else return true;
}
