#include "substring.h"

int substring_position(const char* sub, const char* str){
    
    int c = -1;
    
    if(!sub[0]){
        return 0;
    }
    
    while(str[0]){
        c++;
        
        if(is_prefix(sub, str)){
            return c;
        }
        
        str++;
    }
    
    return -1;
}

bool is_prefix(const char* p, const char* s){
    
    if(!p[0]){
        return true;
    }
    
    if(s[0]){
        if(p[0] == s[0]){
            if(is_prefix(p + 1, s + 1)){
                return true;
            }
        }
    }
    
    return false;
}

int substring_position2(const char* n, const char* h, const char* t){
    // 29 chars!
    return(t=strstr(h,n))?t-h:-1;
}

