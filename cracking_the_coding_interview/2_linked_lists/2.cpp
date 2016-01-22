/* 2.2 | Kth to last
 * -----------------------------------------------------------------------------
 * Desc  : return kth to last element
 *
 * Notes :
 */

#include <forward_list>
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]){

  if(argc != 2) return 1;

  int key = atoi(argv[1]);

  forward_list<int> list(10);

  int i = 0;

  for(auto it = list.begin(); it != list.end(); ++it){
    *it = ++i;
  }

  for(auto it = list.begin(); it != list.end(); ++it){
    cout<<*it<<endl;
  }

  int count = 0;

  for(auto it = list.begin(); it != list.end(); ++it) count++;

  auto it = list.begin();

  if(count >= key) return 0;

  i = 0;
  while(count - i - 1 != key){
    it++;
    i++;
  }

  cout<<"Kth "<<*it<<endl;

  return 0;
}
