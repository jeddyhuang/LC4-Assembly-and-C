#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"

int read_token (token *theToken, char* input) {
  int i;
  int len = strlen(input);
  int latch = 1;
  if(!strcmp(input,"defun")) {
    theToken->type = DEFUN;
    return 0;
  }
  if(!strcmp(input,"return")) {
    theToken->type = RETURN;
    return 0;
  }
  if(!strcmp(input,"+")) {
    theToken->type = PLUS;
    return 0;
  }
  if(!strcmp(input,"-")) {
    theToken->type = MINUS;
    return 0;
  }
  if(!strcmp(input,"*")) {
    theToken->type = MUL;
    return 0;
  }
  if(!strcmp(input,"/")) {
    theToken->type = DIV;
    return 0;
  }
  if(!strcmp(input,"%")) {
    theToken->type = MOD;
    return 0;
  }
  if(!strcmp(input,"and")) {
    theToken->type = AND;
    return 0;
  }
  if(!strcmp(input,"or")) {
    theToken->type = OR;
    return 0;
  }
  if(!strcmp(input,"not")) {
    theToken->type = NOT;
    return 0;
  }
  if(!strcmp(input,"lt")) {
    theToken->type = LT;
    return 0;
  }
  if(!strcmp(input,"le")) {
    theToken->type = LE;
    return 0;
  }
  if(!strcmp(input,"eq")) {
    theToken->type = EQ;
    return 0;
  }
  if(!strcmp(input,"ge")) {
    theToken->type = GE;
    return 0;
  }
  if(!strcmp(input,"gt")) {
    theToken->type = GT;
    return 0;
  }
  if(!strcmp(input,"if")) {
    theToken->type = IF;
    return 0;
  }
  if(!strcmp(input,"else")) {
    theToken->type = ELSE;
    return 0;
  }
  if(!strcmp(input,"endif")) {
    theToken->type = ENDIF;
    return 0;
  }
  if(!strcmp(input,"drop")) {
    theToken->type = DROP;
    return 0;
  }
  if(!strcmp(input,"dup")) {
    theToken->type = DUP;
    return 0;
  }
  if(!strcmp(input,"swap")) {
    theToken->type = SWAP;
    return 0;
  }
  if(!strcmp(input,"rot")) {
    theToken->type = ROT;
    return 0;
  }
  if(len >= 2) {
    if((len == 4) || (len == 5)) {
      if((input[0] == 'a') && (input[1] == 'r') && (input[2] == 'g')) {
        if((len == 4) && (isdigit(input[3]))) {
          theToken->type = ARG;
          theToken->arg_no = atoi(input + 3);
          return 0;
        }
        if((len == 5) && (isdigit(input[3])) && (isdigit(input[4]))) {
          i = atoi(input + 3);
          if(i <= 20) {
            theToken->type = ARG;
            theToken->arg_no = i;
            return 0;
          }
        }
      }
    }
    if((input[0] == '0') && (input[1] == 'x')) {
      latch = 1;
      for(i = 2; i < len; i++) {
        if(!isxdigit(input[i])) latch = 0;
      }
      if(latch) {
        theToken->type = LITERAL;
        theToken->literal_value = strtol(input, NULL, 16);
        return 0;
      }
    }
    if(input[0] == '-') {
      latch = 1;
      for(i = 1; i < len; i++) {
        if(!isdigit(input[i])) latch = 0;
      }
      if(latch) {
        theToken->type = LITERAL;
        theToken->literal_value = atoi(input);
        return 0;
      }
    }
  }
  if(len >= 1) {
    latch = 1;
    for(i = 0; i < len; i++) {
      if(!isdigit(input[i])) latch = 0;
    }
    if(latch) {
      theToken->type = LITERAL;
      theToken->literal_value = atoi(input);
      return 0;
    }
    if(!isalpha(input[0])) {
      theToken->type = BAD_TOKEN;
      strcpy(theToken->str, input);
      return 1;
    }
    latch = 1;
    for(i = 1; i < len; i++) {
      if(!((isalnum(input[i])) || (input[i] == '_'))) latch = 0;
    }
    if(latch) {
      theToken->type = IDENT;
      strcpy(theToken->str, input);
      return 0;
    }
  }
  theToken->type = BAD_TOKEN;
  strcpy(theToken->str, input);
  return 1;
}

void print_token (token *theToken) {
  printf("type is %d\n", theToken->type);
  if(theToken->literal_value) {
    printf("literal_value is %d\n", theToken->literal_value);
  }
  if(theToken->arg_no) {
    printf("arg_no is %d\n", theToken->arg_no);
  }
  printf("str is %s\n", theToken->str);
}