#ifndef LISTS_H
#define LISTS_H

#include <iostream>

template <typename T>
class SinglyLinkedList {
  private:
    struct Node{
      Node* next;
      T x;
    };

    Node* root;
    Node* last;

  public:
    SinglyLinkedList(T _x){
      root = new Node;
      root->next = NULL;
      root->x = _x;
      last = root;
    }

    ~SinglyLinkedList(){
      Node* tbd = root; // To Be Deleted
      Node* tmp;

      while(tbd){
        tmp = tbd->next;
        delete tbd;
        tbd = tmp->next;
      }

      delete root;
    }

    void add(T x){
      // Allocate memory
      last->next = new Node;

      // Redirect pointers
      last = last->next;

      // Initialize the vars of the new node
      last->next = NULL;
      last->x = x;
    }

    void traverse(){
      Node* tmp = root;
      while(tmp){
        std::cout<<tmp->x<<std::endl;
        tmp = tmp->next;
      }
    }

    void deleteAllX(T x){
      Node* tmp = root;
      Node* prev;

      if(root->x == x) 
      while(tmp){
        prev = tmp;
        if(tmp->x == x)
      }
    }

    T getX(){
      return root->x;
    }

};

#endif
