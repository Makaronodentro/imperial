#include "words.h"

void reverse(const char* str, char* rev){

    int n = strlen(str);

    for(int i = 0; i < n; i++){
        rev[i] = str[n - i - 1];
    }
}

bool compare(const char* s1, const char* s2){
    while(s1[0] && !isalpha(s1[0])) s1++;
    while(s2[0] && !isalpha(s2[0])) s2++;
    
    if(!s1[0] && !s2[0]) return true;
    
    if(toupper(s1[0]) == toupper(s2[0])){
        if(compare(s1 + 1, s2 + 1)){
            return true;
        }
    }
    
    return false;
}

bool palindrome(const char* palin){
    char rev[9] = "";
    
    reverse(palin, rev);
    
    cout<<rev<<endl;
    
    if(compare(palin, rev)) return true;
    
    return false;
}

bool anagram(const char* s1, const char* s2){
    
    int c1 = 0, c2 = 0;
    
    while(s1[0] && s2[0]){
        while(s1[0] && !isalpha(s1[0])) s1++;
        while(s2[0] && !isalpha(s2[0])) s2++;
        
        if(!s1[0] || !s2[0]) break;
        
        c1 += toupper(s1[0]);
        c2 += toupper(s2[0]);
        
        s1++;
        s2++;
    }
    
    if(c1 == c2) return true;

    return false;
}