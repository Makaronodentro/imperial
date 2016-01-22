#include <iostream>

class A{

public:
  A(){
    foo();
  }

  virtual void foo(int a = 10){
    std::cout<<"A is "<<a<<std::endl;
  }
};

class B : public A {

public:
  B(){
    foo();
  }

  virtual void foo(int b = 20){
    std::cout<<"B is "<<b<<std::endl;
  }
};

class C : public B {

public:
  C(){
    foo();
  }

  virtual void foo(int c = 30){
    std::cout<<"C is "<<c<<std::endl;
  }
};

int main(){

  A* a = new B();
  a->foo();

  std::cout<<"New line"<<std::endl;

  A* c = new C();
  c->foo();

  delete a;
  delete c;

  return 0;
}
