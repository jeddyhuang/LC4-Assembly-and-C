#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "execute.h"

void execute_insn (MachineState *theMachineState, INSN theINSN) {
  unsigned short int currPC = theMachineState->PC;
  unsigned short int PSR = theMachineState->PSR;
  unsigned short int address;
  signed short int NZP;
  if (currPC == 0x80FF) {
    printf("PC is 80FF. Exiting LC4.\n");
    free(theMachineState);
    exit(EXIT_SUCCESS);
  }
  if ((currPC >= 0x2000) && (currPC <= 0x7FFF)) {
    printf("ERROR: trying to interpret user data as code. Exiting LC4.\n");
    free(theMachineState);
    exit(EXIT_FAILURE);
  }
  if (currPC >= 0xA000) {
    printf("ERROR: trying to interpret OS data as code. Exiting LC4.\n");
    free(theMachineState);
    exit(EXIT_FAILURE);
  }
  if ((currPC >= 0x8000) && (currPC <= 0x9FFF) && (PSR >> 15 == 0x0)) {
    printf("ERROR: trying to execute OS code in user mode. Exiting LC4.\n");
    free(theMachineState);
    exit(EXIT_FAILURE);
  }
  
  switch (theINSN.type) {
    case ILLEGAL_INSN:
      printf("Encountered Illegal INSN. Exiting LC4.\n");
      free(theMachineState);
      exit(EXIT_FAILURE);
    case NOP:
      theMachineState->PC = currPC + 1;
      return;
    case BRp:
      if ((PSR & 0x1) == 0x1) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRz:
      if ((PSR & 0x2) == 0x2) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRzp:
      if (((PSR & 0x2) == 0x2) || ((PSR & 0x1) == 0x1)) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRn:
      if ((PSR & 0x4) == 0x4) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRnp:
      if (((PSR & 0x4) == 0x4) || ((PSR & 0x1) == 0x1)) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRnz:
      if (((PSR & 0x4) == 0x4) || ((PSR & 0x2) == 0x2)) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case BRnzp:
      if (((PSR & 0x4) == 0x4) || ((PSR & 0x2) == 0x2) || ((PSR & 0x1) == 0x1)) {
        theMachineState->PC = (unsigned) (currPC + 1 + (signed) theINSN.immediate);
      } else {
        theMachineState->PC = currPC + 1;
      }
      return;
    case ADD:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] + (signed) theMachineState->R[theINSN.Rt]);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case MUL:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] * (signed) theMachineState->R[theINSN.Rt]);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case SUB:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] - (signed) theMachineState->R[theINSN.Rt]);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case DIV:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] / (signed) theMachineState->R[theINSN.Rt]);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case ADDI:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] + (signed) theINSN.immediate);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case MOD:
      theMachineState->R[theINSN.Rd] = (unsigned) ((signed) theMachineState->R[theINSN.Rs] % (signed) theMachineState->R[theINSN.Rt]);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case AND:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] & theMachineState->R[theINSN.Rt];
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case NOT:
      theMachineState->R[theINSN.Rd] = ~theMachineState->R[theINSN.Rs];
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case OR:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] | theMachineState->R[theINSN.Rt];
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case XOR:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] ^ theMachineState->R[theINSN.Rt];
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case ANDI:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] & theINSN.immediate;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case LDR:
      address = (unsigned) (theMachineState->R[theINSN.Rs] + (signed) theINSN.immediate);
      if (address <= 0x1FFF) {
        printf("ERROR: trying to interpret user code as data. Exiting LC4.\n");free(theMachineState);
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      if ((address >= 0x8000) && (address <= 0x9FFF)) {
        printf("ERROR: trying to interpret OS code as data. Exiting LC4.\n");
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      if ((address >= 0xA000) && (PSR >> 15 == 0x0)) {
        printf("ERROR: trying to access OS data in user mode. Exiting LC4.\n");
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      theMachineState->R[theINSN.Rd] = theMachineState->memory[address];
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case STR:
      address = (unsigned) (theMachineState->R[theINSN.Rs] + (signed) theINSN.immediate);
      if (address <= 0x1FFF) {
        printf("ERROR: trying to interpret user code as data. Exiting LC4.\n");free(theMachineState);
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      if ((address >= 0x8000) && (address <= 0x9FFF)) {
        printf("ERROR: trying to interpret OS code as data. Exiting LC4.\n");
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      if ((address >= 0xA000) && (PSR >> 15 == 0x0)) {
        printf("ERROR: trying to access OS data in user mode. Exiting LC4.\n");
        free(theMachineState);
        exit(EXIT_FAILURE);
      }
      theMachineState->memory[address] = theMachineState->R[theINSN.Rt];
      theMachineState->PC = currPC + 1;
      return;
    case CONST:
      theMachineState->R[theINSN.Rd] = theINSN.immediate;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case HICONST:
      theMachineState->R[theINSN.Rd] = (theMachineState->R[theINSN.Rd] & 0xFF) | (theINSN.immediate << 8);
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case CMP:
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) ((signed) theMachineState->R[theINSN.Rs] - (signed) theMachineState->R[theINSN.Rt]);
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case CMPU:
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) (theMachineState->R[theINSN.Rs] - theMachineState->R[theINSN.Rt]);
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case CMPI:
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) ((signed) theMachineState->R[theINSN.Rs] - (signed) theINSN.immediate);
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case CMPIU:
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) (theMachineState->R[theINSN.Rs] - theINSN.immediate);
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case SLL:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] << theINSN.immediate;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case SRA:
      NZP = (signed) theMachineState->R[theINSN.Rs];
      NZP = NZP >> theINSN.immediate;
      theMachineState->R[theINSN.Rd] = (unsigned) NZP;
      theMachineState->PSR = PSR & 0x8000;
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case SRL:
      theMachineState->R[theINSN.Rd] = theMachineState->R[theINSN.Rs] >> theINSN.immediate;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[theINSN.Rd];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      theMachineState->PC = currPC + 1;
      return;
    case JSRR:
      theMachineState->PC = theMachineState->R[theINSN.Rs];
      theMachineState->R[7] = currPC + 1;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[7];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      return;
    case JSR:
      theMachineState->PC = (currPC & 0x8000) | (theINSN.immediate << 4);
      theMachineState->R[7] = currPC +1;
      theMachineState->PSR = PSR & 0x8000;
      NZP = (signed) theMachineState->R[7];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      return;
    case JMPR:
      theMachineState->PC = theMachineState->R[theINSN.Rs];
      return;
    case JMP:
      theMachineState->PC = currPC + 1 + theINSN.immediate;
      return;
    case TRAP:
      theMachineState->R[7] = currPC +1;
      theMachineState->PC = 0x8000 | theINSN.immediate;
      theMachineState->PSR = 0x8000;
      NZP = (signed) theMachineState->R[7];
      if (NZP < 0) {
        theMachineState->PSR += 4;
      } else if (NZP > 0) {
        theMachineState->PSR += 1;
      } else {
        theMachineState->PSR += 2;
      }
      return;
    case RTI:
      theMachineState->PC = theMachineState->R[7];
      theMachineState->PSR = PSR & 0x7FFF;
      return;
    default:
      return;
  }
}