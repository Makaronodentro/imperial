#include "braille.h"

Braille::Braille(){

    // Populate Letters array
	braille['a'] = "0.....";
	braille['b'] = "00....";
    braille['c'] = "0..0..";
	braille['d'] = "0..00.";
	braille['e'] = "0...0.";
	braille['f'] = "00.0..";
	braille['g'] = "00.00.";
	braille['h'] = "00..0.";
	braille['i'] = ".0.0..";
	braille['g'] = ".0.00.";
	braille['k'] = "0.0...";
	braille['l'] = "000...";
	braille['m'] = "0.00..";
	braille['n'] = "0.000.";
	braille['o'] = "0.0.0.";
	braille['p'] = "0000..";
	braille['q'] = "00000.";
	braille['r'] = "000.0.";
	braille['s'] = ".000..";
	braille['t'] = ".0000.";
	braille['u'] = "0.0..0";
	braille['v'] = "000..0";
	braille['w'] = ".0.000";
	braille['x'] = "0.00.0";
	braille['y'] = "0.0000";
	braille['z'] = "0.0.00";

    braille[' '] = ".....0";

	braille['0'] = "..0000";
    
    braille['.'] = ".0..00";
    
    braille[','] = ".0....";
    
    braille[';'] = ".00...";
    
    braille['-'] = "..0..0";
    
    braille['!'] = ".00.0.";
    
    braille['?'] = ".00..0";
    
    braille['('] = ".00.00";
    braille[')'] = ".00.00";
}

int encode_character(const char c, char* br){
    
    strcpy(br, "");
    
    Braille* d = new Braille();
    
    // if it is a letter 
    if(isalpha(c)){
        if(isupper(c)){
            strcpy(br, d->braille[' ']);
            strcat(br, d->braille[tolower(c)]);
        }
        else{
            strcpy(br, d->braille[c]);
        }
    }
    else if(isdigit(c)){
        strcpy(br, d->braille['0']);
        
        if(c == '0'){
            strcat(br, d->braille['j']);
        }
        else{
            char i = 'a' + c - '1';
            strcat(br, d->braille[i]);
        }
    }
    else if(ispunct(c)){
        strcpy(br, d->braille[c]);
    }
    
    return strlen(br);
}

void encode(const char* str, char* br){
    
    strcpy(br, "");
    
    char container[512] = "";
    
    while(str[0]){
        encode_character(str[0], container);
        strcat(br, container);
        str++;
        
        while(str[0] && str[0] == ' ') str++;
    }
}

void print_braille(const char* str, ostream& out){
    
    char br[512] = "";
    
    char l1[256] = "";
    char l2[256] = "";
    char l3[256] = "";
    
    encode(str, br);
    
    int i = 0;
    
    while(*(br+i)){
        strncat(l1, (br+i), 1);
        i += 1;
        strncat(l2, (br+i), 1);
        i += 1;
        strncat(l3, (br+i), 1);
        i += 1;
        strncat(l1, (br+i), 1);
        i += 1;
        strncat(l2, (br+i), 1);
        i += 1;
        strncat(l3, (br+i), 1);
        i += 1;
        
        strcat(l1, " ");
        strcat(l2, " ");
        strcat(l3, " ");
    }
    
    out<<l1<<endl;
    out<<l2<<endl;
    out<<l3<<endl;
}