/* 1.5 | One Away
 * -----------------------------------------------------------------------------
 * Desc  : Three edits (insert, remove, replace), check if 1 or 0 edits are
 *         required to make 2 strings equal
 *
 * Notes : Can be done in 1 function too.
 */

#include <bitset>
#include <iostream>
#include <cstring>

using namespace std;

bool oneAway(const char*, const char*);

bool insert(const char*, const char*);
bool replace(const char*, const char*);

int main(int argc, char* argv[]){

  if(argc != 3) return 1;

  if(oneAway(argv[1], argv[2])) cout<<"True"<<endl;
  else cout<<"False"<<endl;

  return 0;
}

bool oneAway(const char* s1, const char* s2){

  if(strlen(s1) == strlen(s2)){
    if(replace(s1, s2)) return true;
  }
  else if(strlen(s1) - strlen(s2) == 1){
    if(insert(s1, s2)) return true;
  }
  else if(strlen(s1) - strlen(s2) == -1){
    if(insert(s2, s1)) return true;
  }

  return false;
}

bool insert(const char* s1, const char* s2){

  bool diff = false;

  while(s1[0]){
    if(s1[0] != s2[0]){
      s1++;
      if(diffs) return false;
      diffs = true;
    }

    s1++;
    s2++;
  }

  return true;
}

bool replace(const char* s1, const char* s2){
  int diffs = 0;

  while(s1[0]){
    if(s1[0] != s2[0]){
      if(++diffs > 1) return false;
    }
    s1++;
    s2++;
  }

  return true;
}
