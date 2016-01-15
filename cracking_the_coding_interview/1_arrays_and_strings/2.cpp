/* 1.2 | checkPermutation
 * -----------------------------------------------------------------------------
 * Desc  : Check if one string is a permutation of the other
 *
 * Notes : Hash-table, bitset
 */

 #include <bitset>
 #include <iostream>
 #include <cstring>

 using namespace std;

bool checkPermutation(const char*, const char*);

int main(int argc, char* argv[]){

    if(checkPermutation(argv[1], argv[2])) cout<<"True"<<endl;
    else cout<<"False"<<endl;

    return 0;
}

bool checkPermutation(const char* s1, const char* s2){

    if(strlen(s1) != strlen(s2)) return false;

    int ch1[128], ch2[128];

    for(int i = 0; i < 128; i++){
      ch1[i] = 0;
      ch2[i] = 0;
    }

    while(s1[0]){
        ch1[s1[0]]++;
        s1++;

        ch2[s2[0]]++;
        s2++;
    }

    for(int i = 0; i < 128; i++){
      if(ch1[i] != ch2[i]) return false;
    }

    return true;
}
