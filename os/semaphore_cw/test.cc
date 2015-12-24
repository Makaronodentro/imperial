#include <iostream>

using namespace std;

void test(int* c, int& a, int& b){
    a++;
    b += 2;
    *c = 10;
}

int main(){
    int a = 0;
    int b = 0;
    int* c = new int;
    
    test(c, a, b);
    
    cout<<a<<" "<<b<<" "<<*c<<endl;
    
    return 0;
}