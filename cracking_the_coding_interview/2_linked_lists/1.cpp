/* 2.1 | Remove Dupes
 * -----------------------------------------------------------------------------
 * Desc  : remove duplicates from unsorted list
 *
 * Notes : Do we care about running time or memory?
 *         Hash table: O(N) running time | Progressively iterate O(N^2)
 */

#include <iostream>
#include <list>
#include <cmath>

using namespace std;

void deleteDups(list<int>& ml){
  list<int>::iterator it1 = ml.begin(), it2 = ml.begin();
  it2++;

  while(it1 != ml.end()){
    while(it2 != ml.end()){
      if(*it2 == *it1){
        it2 = ml.erase(it2);
      }
      else{
        it2++;
      }
    }
    it1++;
    it2 = it1;
    it2++;
  }
}

int main(int argc, char* argv[]){

  list<int> ml;
  list<int>::iterator it;

  // set some values:
  for (int i=0; i<100; ++i){
      ml.push_back(rand() % 5);
  }

  int count = 0;
  for(it = ml.begin(); it != ml.end(); it++){
    cout<<*it<<" ";
    count++;
  }

  cout<<endl<<count<<endl;

  deleteDups(ml);

  count = 0;
  for(it = ml.begin(); it != ml.end(); it++){
    cout<<*it<<" ";
    count++;
  }

  cout<<endl<<count<<endl;

  return 0;
}
