#ifndef LISTS_H
#define LISTS_H

#include <iostream>

template <typename T>
struct Node{
  Node* next;
  T x;
};

template <typename T>
class SinglyLinkedList {
  private:

    Node<T>* root;

  public:
    SinglyLinkedList(T _x){
      root = new Node<T>;
      root->next = NULL;
      root->x = _x;
      last = root;
    }

    ~SinglyLinkedList(){
      Node<T>* tbd = root; // To Be Deleted
      Node<T>* tmp;

      while(tbd){
        tmp = tbd->next;
        delete tbd;
        tbd = tmp->next;
      }

      delete root;
    }

    void addFront(T x){
      // Allocate memory
      Node<T>* tmp = new Node;

      // Make the new node point to root
      tmp->next = root;

      // Set new root
      root = tmp;
    }

    void traverse(){
      Node<T>* tmp = root;
      while(tmp){
        std::cout<<tmp->x<<std::endl;
        tmp = tmp->next;
      }
    }

    T getX(){
      return root->x;
    }
};

#endif
