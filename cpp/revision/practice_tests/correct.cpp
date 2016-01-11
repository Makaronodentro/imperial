#include "correct.h"

/* You are supplied with two helper functions */

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(const char* binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */

void text_to_binary(const char* txt, char* bin){
  char word[9];
  
  while(txt[0]){
    ascii_to_binary(txt[0], word);
    strcat(bin, word);
    txt++;
  }
}

void binary_to_text(const char* bin, char* txt){
  char str[16] = "";

  int i = 0;
  
  while(bin[0]){
    strncpy(str, bin, 8);
    txt[i] = binary_to_ascii(str);
    i++;
    bin += 8;
  }
}

void add_error_correction(const char* str, char* correct){
  strcpy(correct, "");
  
  char fbit[5];
  int d[4];
  int c[3];
  char sbit[8];

  // c1,c2,d1,c3,d2,d3,d4
  while(str[0]){
    strncpy(fbit, str, 4);
    d[0] = fbit[0] - '0';
    d[1] = fbit[1] - '0';
    d[2] = fbit[2] - '0';
    d[3] = fbit[3] - '0';
    
    c[0] = (d[0] + d[1] + d[3]) % 2;
    c[1] = (d[0] + d[2] + d[3]) % 2;
    c[2] = (d[1] + d[2] + d[3]) % 2;

    sbit[0] = c[0] + '0';
    sbit[1] = c[1] + '0';
    sbit[2] = d[0] + '0';
    sbit[3] = c[2] + '0';
    sbit[4] = d[1] + '0';
    sbit[5] = d[2] + '0';
    sbit[6] = d[3] + '0';
    sbit[7] = '\0';

    strcat(correct, sbit);

    str += 4;
  }
}

int decode(char* s1, char* s2){
  strcpy(s2, "");
  
  char sbit[8];
  int p[3];
  int b[7];
  int err_i, err_c = 0;
  char fbit[5];

  while(s1[0]){
    // take 7 digits
    strncpy(sbit, s1, 7);
    
    b[0] = sbit[0] - '0';
    b[1] = sbit[1] - '0';
    b[2] = sbit[2] - '0';
    b[3] = sbit[3] - '0';
    b[4] = sbit[4] - '0';
    b[5] = sbit[5] - '0';
    b[6] = sbit[6] - '0';

    // calculate parities
    p[0] = (b[3] + b[4] + b[5] + b[6]) % 2;
    p[1] = (b[1] + b[2] + b[5] + b[6]) % 2;
    p[2] = (b[0] + b[2] + b[4] + b[6]) % 2;

    if(p[0] + p[1] + p[2] != 0){
      err_i = p[0] * 4 + p[2] * 2 + p[1] * 1;

      b[err_i] = (b[err_i] + 1) % 2;

      err_c++;
    }
    
    fbit[0] = b[2] + '0';
    fbit[1] = b[4] + '0';
    fbit[2] = b[5] + '0';
    fbit[3] = b[6] + '0';
    fbit[4] = '\0';
    
    strcat(s2, fbit);

    s1 += 7;
  }

  return err_c;
}
