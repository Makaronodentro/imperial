/*
* User Input Function
*/
#include "helper.h"
#include <iostream>

string getInput(){
    string str(""), tmp("");
    while(cin>>ws>>tmp){
        str += tmp;
    }

    return str;
}