#include <iostream>
#include "substring.h"

using namespace std;

int main() {
    
  cout << substring_position("this", "this is a simple exercise") << endl;
  cout << substring_position("is", "this is a simple exercise") << endl;
  cout << substring_position("is a", "this is a simple exercise") << endl;
  cout << substring_position("is an", "this is a simple exercise") << endl;
  cout << substring_position("exercise", "this is a simple exercise") << endl;
  cout << substring_position("simple exercise", "this is a simple") << endl;
  cout << substring_position("", "this is a simple exercise") << endl;
  cout << substring_position("", "") << endl;
  
  cout<<endl;
  
  cout << substring_position2("this", "this is a simple exercise") << endl;
  cout << substring_position2("is", "this is a simple exercise") << endl;
  cout << substring_position2("is a", "this is a simple exercise") << endl;
  cout << substring_position2("is an", "this is a simple exercise") << endl;
  cout << substring_position2("exercise", "this is a simple exercise") << endl;
  cout << substring_position2("simple exercise", "this is a simple") << endl;
  cout << substring_position2("", "this is a simple exercise") << endl;
  cout << substring_position2("", "") << endl;
  
  return 0;
}