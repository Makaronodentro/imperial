/* 2.1 | Remove Dupes
 * -----------------------------------------------------------------------------
 * Desc  : remove duplicates from unsorted list
 *
 * Notes : Do we care about running time or memory?
 *         Hash table: O(N) running time | Progressively iterate O(N^2)
 */

#include "lists.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){

  SinglyLinkedList<int>* list = new SinglyLinkedList<int>(5);

  int i = 0;
  while(i < 5){
    list->add(i);
    cout<<"adding "<<i<<endl;

    i++;
  }

  list->traverse();

  delete list;

  return 0;
}
