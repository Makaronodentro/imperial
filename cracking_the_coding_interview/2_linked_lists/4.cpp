/* 2.4 | Partition
 * -----------------------------------------------------------------------------
 * Desc  : place els < x at the beginning, els> x at the end
 *
 * Notes :
 */

#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct Node{
    Node* next;
    int x;
};

void partition(Node* root, int n){
  Node* front = root;
  Node* back = root;



  Node* tmp = root;
  while(tmp != NULL){
    Node* next = tmp->next;
    if(tmp->x < n){
      tmp->next = front;
      front = tmp;
    }
    else{
      tmp->next = back;
      back = tmp;
    }
    tmp = next;
  }

  back->next = NULL;

  root = front;
}

int main(int argc, char* argv[]){

  Node* root = new Node;

  root->x = 0;
  root->next = NULL;

  Node* tmp = root;
  for(int i = 1; i < 20; i++){
    tmp->next = new Node;
    tmp = tmp->next;
    tmp->x = i;
    tmp->next = NULL;
  }

  tmp = root;
  while(tmp->next != NULL){
    cout<<tmp->x<<" "<<endl;
    tmp = tmp->next;
  }

  partition(root, 5);

  tmp = root;
  while(tmp->next != NULL){
    cout<<tmp->x<<" "<<endl;
    tmp = tmp->next;
  }

  return 0;
}
