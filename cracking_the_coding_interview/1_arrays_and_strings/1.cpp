/* 1.1 | isUnique
 * -----------------------------------------------------------------------------
 * Desc  : Determine if a string has only unique characters
 *
 * Notes : Hash-table, bitset 
 */
 
 #include <bitset>
 #include <iostream>
 #include <cstring>
 
 using namespace std;
 
bool isUnique(const char*);
 
int main(int argc, char* argv[]){
    
    if(isUnique(argv[1])) cout<<"True"<<endl;
    else cout<<"False"<<endl;
    
    return 0;
}

bool isUnique(const char* str){
    
    if(strlen(str) > 128) return false;
    
    bitset<128> ch;
    
    while(str[0]){
        
        if(ch[str[0]] == 1) return false;
        
        ch.set(str[0]);
        str++;
    }
    
    return true;
}