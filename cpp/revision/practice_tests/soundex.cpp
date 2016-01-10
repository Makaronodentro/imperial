#include "soundex.h"

void encode(const char* surname, char* soundex){
    
    // Wipe soundex
    // for(int i = 0; i < strlen(soundex); i++){
    //     soundex[i] = 0;
    // }
    
    // 1. The letter at the start of the surname is the first soundex letter
    if(surname[0]){
        soundex[0] = toupper(surname[0]);
        surname++;
    }
    else{
        return;
    }
    
    int c = 1;
    
    while(surname[0] && c < 4){
    
    // 2. Get soundex code for current char
    
    // Skip? a, e, h, i, o, u, w and y are ignored
        if(skip(surname[0])){
            surname++;
            continue;
        }
    //    b,f,p,v →1 || c,g,j,k,q,s,x,z → 2 || d,t→3 
    //           l→4 ||             m,n → 5 ||  r→6
        char cur_char = getCode(surname[0]);
        surname++;
    
    // 3. letters with the same soundex encoding are skipped
        if(cur_char == soundex[c - 1]){
            continue;
        }
        else{
            soundex[c] = cur_char;
            c++;
        }
    }
    
    // add zeroes at the end
    while(c < 4){
        soundex[c] = '0';
        c++;
    }
}

bool skip(char c){
    if(c == 'a' || c == 'e' || c == 'h' || c == 'i' || c == 'o' ||  c == 'u' ||  c == 'w' ||  c == 'y'){
        return true;
    }
    
    return false;
}

char getCode(char c){
    if(c == 'b' || c == 'f' || c == 'p' || c == 'v'){
        return '1';
    }
    
    if(c == 'c' || c == 'g' || c == 'j' || c == 'k' || c == 'q' ||  c == 's' ||  c == 'x' ||  c == 'z'){
        return '2';
    }
    
    if(c == 'd' || c == 't'){
        return '3';
    }
    
    if(c == 'l'){
        return '4';
    }
    
    if(c == 'm' || c == 'n'){
        return '5';
    }
    
    if(c == 'r'){
        return '6';
    }
    
    return '\0';
}

bool compare(const char* s1, const char*s2){
    
    while(s1[0] && s2[0]){
        if(s1[0] != s2[0]){
            return false;
        }
        
        s1++;
        s2++;
    }
    
    return true;
}

int count(const char* surname, const char* sentence){
    char soundex1[5] = "";
    char soundex2[5] = "";
    char word[27] = "";
    encode(surname, soundex1);
    
    int count = 0;
    
    // Get word
    while(sentence[0]){
        
        // Get word
        int c = 0;
        while(sentence[0] && isalpha(sentence[0])){
            word[c] = sentence[0];
            c++;
            sentence++;
        }
        
        // Skip trailing spaces
        while(sentence[0] && !isalpha(sentence[0])) sentence++;
        
        encode(word, soundex2);
        
        cout<<"Passing "<<word<<" receiving "<<soundex2<<endl;
        cout<<"Compare with "<<soundex1<<endl;
        
        if(compare(soundex1, soundex2)) count++;
        
        // erase word
        for(int i = 0; i < 27; i++){
            word[i] = '\0';
        }
    }

    return count;
}