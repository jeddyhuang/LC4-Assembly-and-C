#ifndef DECODE_H
#define DECODE_H
/*
 * decode.h
 */

// INSN_TYPE : This enumerated type is used to represent all of the types of LC4 instructions
// Note that ADDI and ANDI are to be used to denote ADD Immediate and AND Immediate respectively.
typedef enum {ILLEGAL_INSN,
	      NOP, BRp, BRz, BRzp, BRn, BRnp, BRnz, BRnzp,
	      ADD, MUL, SUB, DIV, ADDI,
	      MOD,
	      AND, NOT, OR, XOR, ANDI,
	      LDR, STR,
	      CONST, HICONST,
	      CMP, CMPU, CMPI, CMPIU,
	      SLL, SRA, SRL,
	      JSRR, JSR,
	      JMPR, JMP,
	      TRAP, RTI} INSN_TYPE;

// Structure used to represent LC4 instructions
typedef struct {
  INSN_TYPE type;       // Type of the instruction
  int Rd, Rs, Rt;       // Register fields
  short int immediate;  // Immediate field of instruction 
}  INSN;


// decode_insn : This function takes as input an unsigned 16 bit pattern and decodes that into
// an INSN structure that breaks out the various instruction components.
INSN decode_insn (unsigned short int insn);

// Print a readable version of the instruction out to the specified file
void print_insn (FILE *theFile, INSN theINSN);

#endif