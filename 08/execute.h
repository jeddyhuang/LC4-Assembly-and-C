#ifndef EXECUTE_H
#define EXECUTE_H
/*
 * execute.h
 */

// Include decode.h
#include "decode.h"

typedef struct {
  unsigned short int PC; // Program Counter
  unsigned short int PSR; // Processor Status Register
  unsigned short int R[8]; // Register file
  unsigned short int memory[65536]; // Processor memory
} MachineState;

/*
 * execute_insn : This function simulates the execution of a single instruction
 * given in theINSN. After the function completes, the structure pointed to by theMachineState
 * should be updated to reflect the action of the instruction.
 */
void execute_insn (MachineState *theMachineState, INSN theINSN);

#endif