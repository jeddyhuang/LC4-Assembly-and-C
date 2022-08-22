#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "execute.h"
#include "loader.h"

int compare(const void* a, const void* b) {
  const int * const ia = a;
  const int * const ib = b;
  if (ia[1] < ib[1]) {
    return 1;
  } else return -1;
}

int main(int argc, char **argv) {
  MachineState *machineState;
  int freq[65536][2];
  FILE *output_file1, *output_file2, *output_file3;
  unsigned short int currPC, address, instr, PSR, color;
  int i;
  INSN decoded;
  if (argc < 3) {
    printf("Incorrect Inputs");
    exit(EXIT_FAILURE);
  }
  machineState = malloc(sizeof(MachineState));
  if (machineState == NULL) {
    printf("Error Building Struct");
    exit(EXIT_FAILURE);
  }
  machineState->PC = 0x8200;
  machineState->PSR = 0x8002;
  for (i = 0; i < 8; i++) {
  	machineState->R[i] = 0;
  }
  for (i = 0; i < 65536; i++) {
    machineState->memory[i] = 0;
    freq[i][0] = i;
    freq[i][1] = 0;
  }
  for (i = 2; i < argc; i++) {
    ReadObjectFile(argv[i], machineState->memory);
  }
  
  output_file1 = fopen(argv[1], "w");
  if (output_file1 == NULL) {
    printf("Error Writing to File");
    free(machineState);
    exit(EXIT_FAILURE);
  }
  
  while (1) {
    currPC = machineState->PC;
    instr = machineState->memory[currPC];
    PSR = machineState->PSR;
    decoded = decode_insn(instr);
    
    if ((decoded.type == LDR) || (decoded.type == STR)) {
      address = (unsigned) (machineState->R[decoded.Rs] + (signed) decoded.immediate);
      if (address <= 0x1FFF) {
        fclose(output_file1);
        output_file1 = NULL;
      }
      if ((address >= 0x8000) && (address <= 0x9FFF)) {
        fclose(output_file1);
        output_file1 = NULL;
      }
      if ((address >= 0xA000) && (PSR >> 15 == 0x0)) {
        fclose(output_file1);
        output_file1 = NULL;
      }
    } else {
      if (currPC == 0x80FF) {
        fclose(output_file1);
        output_file1 = NULL;
      }
      if ((currPC >= 0x2000) && (currPC <= 0x7FFF)) {
        fclose(output_file1);
        output_file1 = NULL;
      }
      if (currPC >= 0xA000) {
        fclose(output_file1);
        output_file1 = NULL;
      }
      if ((currPC >= 0x8000) && (currPC <= 0x9FFF) && (PSR >> 15 == 0x0)) {
        fclose(output_file1);
        output_file1 = NULL;
      }
    }
    
    if (output_file1 == NULL) {
      output_file2 = fopen("image.ppm", "wb");
      if (output_file2 == NULL) {
        printf("Error Writing to File");
        free(machineState);
        exit(EXIT_FAILURE);
      }
      fprintf(output_file2, "P6\n%d %d\n255\n", 128, 124);
      for (i = 0; i < 0x3E00; i++) {
        color = ((machineState->memory[0xC000+i] >> 10) & 0x1F) << 3;
        fwrite(&color, 2, 1, output_file2);
        color = ((machineState->memory[0xC000+i] >> 5) & 0x1F) << 3;
        fwrite(&color, 2, 1, output_file2);
        color = ((machineState->memory[0xC000+i]) & 0x1F) << 3;
        fwrite(&color, 2, 1, output_file2);
      }
      fclose(output_file2);
    }
    
    if (output_file1 == NULL) {
      output_file3 = fopen("insn_frequency.txt", "w");
      if (output_file3 == NULL) {
        printf("Error Writing to File");
        free(machineState);
        exit(EXIT_FAILURE);
      }
      qsort(freq, 65536, sizeof(*freq), compare);
      for (i = 0; i < 65536; i++) {
        if (freq[i][1] != 0) {
          fprintf(output_file3, "%04X : %d\n", freq[i][0], freq[i][1]);
        }
      }
      fclose(output_file3);
    }
    
    freq[currPC][1]++;
    execute_insn(machineState, decoded);
    
    fprintf(output_file1, "%04X ", currPC);
    for (i = 15; i > -1; i--) {
      fprintf(output_file1, "%d", (instr >> i) & 0x1);
    }
    switch (decoded.type) {
      case ILLEGAL_INSN:
      case NOP:
      case BRp:
      case BRz:
      case BRzp:
      case BRn:
      case BRnp:
      case BRnz:
      case BRnzp:
      case JMPR:
      case JMP:
      case RTI:
        fprintf(output_file1, " 0 0 0000 0 0 0 0000 0000\n");
        break;
      case ADD:
      case MUL:
      case SUB:
      case DIV:
      case ADDI:
      case MOD:
      case AND:
      case NOT:
      case OR:
      case XOR:
      case ANDI:
      case CONST:
      case HICONST:
      case SLL:
      case SRA:
      case SRL:
        fprintf(output_file1, " 1 %o %04X 1 %o 0 0000 0000\n", decoded.Rd, machineState->R[decoded.Rd], machineState->PSR & 0x7);
        break;
      case LDR:
        fprintf(output_file1, " 1 %o %04X 1 %o 0 %04X %04X\n", decoded.Rd, machineState->R[decoded.Rd], machineState->PSR & 0x7, address, machineState->memory[address]);
        break;
      case STR:
        fprintf(output_file1, " 0 0 0000 0 0 1 %04X %04X\n", address, machineState->memory[address]);
        break;
      case CMP:
      case CMPU:
      case CMPI:
      case CMPIU:
        fprintf(output_file1, " 0 0 0000 1 %o 0 0000 0000\n", machineState->PSR & 0x7);
        break;
      case JSRR:
      case JSR:
      case TRAP:
        fprintf(output_file1, " 1 7 %04X 1 %o 0 0000 0000\n", machineState->R[7], machineState->PSR & 0x7);
        break;
      default:
        break;
    }
  }
  return 1;
}