#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"
#include "tokenwriter.h"
#include "stack.h"

int defun = 0;
int branch = 0;
int ifnum = 0;

char routinename[251] = {'\0'};

stack *theStack;

int write_token(token *theToken, FILE *outputFile) {
  int value;
  
  switch(theToken->type) {
    case DEFUN:
      defun = 1;
      break;
    case IDENT:
      if(defun) {
        fprintf(outputFile, "    .CODE\n");
        fprintf(outputFile, "    .FALIGN\n");
        fprintf(outputFile, "%s\n", theToken->str);
        fprintf(outputFile, "    ADD R6 R6 #-3\n");
        fprintf(outputFile, "    STR R7 R6 #1\n");
        fprintf(outputFile, "    STR R5 R6 #0\n");
        fprintf(outputFile, "    ADD R5 R6 #0\n");
        defun = 0;
        strcpy(routinename, theToken->str);
      } else {
        fprintf(outputFile, "    JSR %s\n", theToken->str);
        fprintf(outputFile, "    ADD R6 R6 #-1\n");
      }
      break;
    case RETURN:
      fprintf(outputFile, "    LDR R7 R6 #0\n");
      fprintf(outputFile, "    STR R7 R5 #2\n");
      fprintf(outputFile, "    ADD R6 R5 #0\n");
      fprintf(outputFile, "    LDR R5 R6 #0\n");
      fprintf(outputFile, "    LDR R7 R6 #1\n");
      fprintf(outputFile, "    ADD R6 R6 #3\n");
      fprintf(outputFile, "    JMPR R7\n");
      break;
    case PLUS:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    ADD R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case MINUS:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    SUB R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case MUL:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    MUL R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case DIV:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    DIV R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case MOD:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    MOD R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case AND:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    AND R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case OR:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    OR R1 R1 R2\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case NOT:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    NOT R1 R1\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case LT:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMP R1 R2\n");
      fprintf(outputFile, "    BRn lt_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #0\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    JMP END_lt_%d\n", branch);
      fprintf(outputFile, "lt_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #1\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "END_lt_%d\n", branch);
      branch++;
      break;
    case LE:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMP R1 R2\n");
      fprintf(outputFile, "    BRnz le_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #0\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    JMP END_le_%d\n", branch);
      fprintf(outputFile, "le_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #1\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "END_le_%d\n", branch);
      branch++;
      break;
    case EQ:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMP R1 R2\n");
      fprintf(outputFile, "    BRz eq_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #0\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    JMP END_eq_%d\n", branch);
      fprintf(outputFile, "eq_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #1\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "END_eq_%d\n", branch);
      branch++;
      break;
    case GE:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMP R1 R2\n");
      fprintf(outputFile, "    BRzp ge_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #0\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    JMP END_ge_%d\n", branch);
      fprintf(outputFile, "ge_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #1\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "END_ge_%d\n", branch);
      branch++;
      break;
    case GT:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMP R1 R2\n");
      fprintf(outputFile, "    BRp gt_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #0\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    JMP END_gt_%d\n", branch);
      fprintf(outputFile, "gt_%d\n", branch);
      fprintf(outputFile, "    CONST R0 #1\n");
      fprintf(outputFile, "    STR R0 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "END_gt_%d\n", branch);
      branch++;
      break;
    case IF:
      theStack = push(theStack, ifnum);
      fprintf(outputFile, "IF_%s%d\n", routinename, theStack->data);
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    CMPI R1 #0\n");
      fprintf(outputFile, "    BRnz ELSE_%s%d\n", routinename, theStack->data);
      ifnum++;
      break;
    case ELSE:
      theStack->pair = 1;
      fprintf(outputFile, "    BRnzp ENDIF_%s%d\n", routinename, theStack->data);
      fprintf(outputFile, "ELSE_%s%d\n", routinename, theStack->data);
      break;
    case ENDIF:
      if(!theStack->pair) fprintf(outputFile, "ELSE_%s%d\n", routinename, theStack->data);
      fprintf(outputFile, "ENDIF_%s%d\n", routinename, theStack->data);
      theStack = pop(theStack);
      break;
    case DROP:
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      break;
    case DUP:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case SWAP:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    STR R2 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case ROT:
      fprintf(outputFile, "    LDR R1 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R2 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    LDR R3 R6 #0\n");
      fprintf(outputFile, "    ADD R6 R6 #1\n");
      fprintf(outputFile, "    STR R2 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    STR R1 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      fprintf(outputFile, "    STR R3 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case ARG:
      fprintf(outputFile, "    LDR R3 R5 #%d\n", theToken->arg_no + 2);
      fprintf(outputFile, "    STR R3 R6 #-1\n");
      fprintf(outputFile, "    ADD R6 R6 #-1\n");
      break;
    case LITERAL:
      value = theToken->literal_value;
      if((value > 255) || (value < -256)) {
        fprintf(outputFile, "    CONST R3 #%d\n", value & 0xFF);
        fprintf(outputFile, "    HICONST R3 #%d\n", (value >> 8) & 0xFF);
        fprintf(outputFile, "    STR R3 R6 #-1\n");
        fprintf(outputFile, "    ADD R6 R6 #-1\n");
      } else {
        fprintf(outputFile, "    CONST R3 #%d\n", value);
        fprintf(outputFile, "    STR R3 R6 #-1\n");
        fprintf(outputFile, "    ADD R6 R6 #-1\n");
      }
      break;
    case BAD_TOKEN:
      return 1;
    default:
      return 1;
  }
  return 0;
}