#include <stdio.h>
#include <stdlib.h>
#include "decode.h"

#define INSN_OP(I) ((I) >> 12)
#define INSN_11_9(I) (((I) >> 9) & 0x7)
#define INSN_8_6(I) (((I) >> 6) & 0x7)
#define INSN_5_3(I) (((I) >> 3) & 0x7)
#define INSN_2_0(I) ((I) & 0x7)
#define INSN_8_7(I) (((I) >> 7) & 0x3)
#define INSN_11(I) (((I) >> 11) & 0x1)
#define INSN_5_4(I) (((I) >> 4) & 0x3)
#define INSN_IMM11(I) (((I) & 0x7FF) | (((I) & 0x400) ? 0xF800 : 0x0))
#define INSN_IMM9(I) (((I) & 0x1FF) | (((I) & 0x100) ? 0xFE00 : 0x0))
#define INSN_IMM7(I) (((I) & 0x7F) | (((I) & 0x40) ? 0xFF80 : 0x0))
#define INSN_IMM6(I) (((I) & 0x3F) | (((I) & 0x20) ? 0xFFC0 : 0x0))
#define INSN_IMM5(I) (((I) & 0x1F) | (((I) & 0x10) ? 0xFFE0 : 0x0))
#define INSN_UIMM8(I) ((I) & 0xFF)
#define INSN_UIMM7(I) ((I) & 0x7F)
#define INSN_UIMM4(I) ((I) & 0xF)

INSN decode_insn (unsigned short int insn) {
  INSN new_INSN;
  unsigned short int opcode = INSN_OP(insn);
  unsigned short int branch, Rd, Rs, Rt;
  signed short int IMM;
  unsigned short int UIMM;
  
  switch (opcode) {
    case 0:
      branch = INSN_11_9(insn);
      IMM = INSN_IMM9(insn);
      switch (branch) {
        case 0:
          new_INSN.type = NOP;
          break;
        case 1:
          new_INSN.type = BRp;
          new_INSN.immediate = IMM;
          break;
        case 2:
          new_INSN.type = BRz;
          new_INSN.immediate = IMM;
          break;
        case 3:
          new_INSN.type = BRzp;
          new_INSN.immediate = IMM;
          break;
        case 4:
          new_INSN.type = BRn;
          new_INSN.immediate = IMM;
          break;
        case 5:
          new_INSN.type = BRnp;
          new_INSN.immediate = IMM;
          break;
        case 6:
          new_INSN.type = BRnz;
          new_INSN.immediate = IMM;
          break;
        case 7:
          new_INSN.type = BRnzp;
          new_INSN.immediate = IMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 1:
      branch = INSN_5_3(insn);
      Rd = INSN_11_9(insn);
      Rs = INSN_8_6(insn);
      Rt = INSN_2_0(insn);
      IMM = INSN_IMM5(insn);
      new_INSN.Rd = Rd;
      new_INSN.Rs = Rs;
      switch (branch) {
        case 0:
          new_INSN.type = ADD;
          new_INSN.Rt = Rt;
          break;
        case 1:
          new_INSN.type = MUL;
          new_INSN.Rt = Rt;
          break;
        case 2:
          new_INSN.type = SUB;
          new_INSN.Rt = Rt;
          break;
        case 3:
          new_INSN.type = DIV;
          new_INSN.Rt = Rt;
          break;
        case 4:
        case 5:
        case 6:
        case 7:
          new_INSN.type = ADDI;
          new_INSN.immediate = IMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 2:
      branch = INSN_8_7(insn);
      Rs = INSN_11_9(insn);
      Rt = INSN_2_0(insn);
      IMM = INSN_IMM7(insn);
      UIMM = INSN_UIMM7(insn);
      new_INSN.Rs = Rs;
      switch (branch) {
        case 0:
          new_INSN.type = CMP;
          new_INSN.Rt = Rt;
          break;
        case 1:
          new_INSN.type = CMPU;
          new_INSN.Rt = Rt;
          break;
        case 2:
          new_INSN.type = CMPI;
          new_INSN.immediate = IMM;
          break;
        case 3:
          new_INSN.type = CMPIU;
          new_INSN.immediate = UIMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 4:
      branch = INSN_11(insn);
      Rs = INSN_8_6(insn);
      IMM = INSN_IMM11(insn);
      switch (branch) {
        case 0:
          new_INSN.type = JSRR;
          new_INSN.Rs = Rs;
          break;
        case 1:
          new_INSN.type = JSR;
          new_INSN.immediate = IMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 5:
      branch = INSN_5_3(insn);
      Rd = INSN_11_9(insn);
      Rs = INSN_8_6(insn);
      Rt = INSN_2_0(insn);
      IMM = INSN_IMM5(insn);
      new_INSN.Rd = Rd;
      new_INSN.Rs = Rs;
      switch (branch) {
        case 0:
          new_INSN.type = AND;
          new_INSN.Rt = Rt;
          break;
        case 1:
          new_INSN.type = NOT;
          break;
        case 2:
          new_INSN.type = OR;
          new_INSN.Rt = Rt;
          break;
        case 3:
          new_INSN.type = XOR;
          new_INSN.Rt = Rt;
          break;
        case 4:
        case 5:
        case 6:
        case 7:
          new_INSN.type = ANDI;
          new_INSN.immediate = IMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 6:
      Rd = INSN_11_9(insn);
      Rs = INSN_8_6(insn);
      IMM = INSN_IMM6(insn);
      new_INSN.type = LDR;
      new_INSN.Rd = Rd;
      new_INSN.Rs = Rs;
      new_INSN.immediate = IMM;
      break;
    case 7:
      Rt = INSN_11_9(insn);
      Rs = INSN_8_6(insn);
      IMM = INSN_IMM6(insn);
      new_INSN.type = STR;
      new_INSN.Rt = Rt;
      new_INSN.Rs = Rs;
      new_INSN.immediate = IMM;
      break;
    case 8:
      new_INSN.type = RTI;
      break;
    case 9:
      Rd = INSN_11_9(insn);
      IMM = INSN_IMM9(insn);
      new_INSN.type = CONST;
      new_INSN.Rd = Rd;
      new_INSN.immediate = IMM;
      break;
    case 10:
      branch = INSN_5_4(insn);
      Rd = INSN_11_9(insn);
      Rs = INSN_8_6(insn);
      Rt = INSN_2_0(insn);
      UIMM = INSN_UIMM4(insn);
      new_INSN.Rd = Rd;
      new_INSN.Rs = Rs;
      switch (branch) {
        case 0:
          new_INSN.type = SLL;
          new_INSN.immediate = UIMM;
          break;
        case 1:
          new_INSN.type = SRA;
          new_INSN.immediate = UIMM;
          break;
        case 2:
          new_INSN.type = SRL;
          new_INSN.immediate = UIMM;
          break;
        case 3:
          new_INSN.type = MOD;
          new_INSN.Rt = Rt;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 12:
      branch = INSN_11(insn);
      Rs = INSN_8_6(insn);
      IMM = INSN_IMM11(insn);
      switch (branch) {
        case 0:
          new_INSN.type = JMPR;
          new_INSN.Rs = Rs;
          break;
        case 1:
          new_INSN.type = JMP;
          new_INSN.immediate = IMM;
          break;
        default:
          new_INSN.type = ILLEGAL_INSN;
      }
      break;
    case 13:
      Rd = INSN_11_9(insn);
      UIMM = INSN_UIMM8(insn);
      new_INSN.type = HICONST;
      new_INSN.Rd = Rd;
      new_INSN.immediate = UIMM;
      break;
    case 15:
      UIMM = INSN_UIMM8(insn);
      new_INSN.type = TRAP;
      new_INSN.immediate = UIMM;
      break;
    default:
      new_INSN.type = ILLEGAL_INSN;
  }
  return new_INSN;
}

void print_insn (FILE *theFile, INSN theINSN) {
  int Rd = theINSN.Rd;
  int Rs = theINSN.Rs;
  int Rt = theINSN.Rt;
  short int IMM = theINSN.immediate;
  switch (theINSN.type) {
    case ILLEGAL_INSN:
      fprintf(theFile, "INVALID INSTRUCTION");
      return;
    case NOP:
      fprintf(theFile, "NOP");
      return;
    case BRp:
      fprintf(theFile, "BRp #%d", IMM);
      return;
    case BRz:
      fprintf(theFile, "BRz #%d", IMM);
      return;
    case BRzp:
      fprintf(theFile, "BRzp #%d", IMM);
      return;
    case BRn:
      fprintf(theFile, "BRn #%d", IMM);
      return;
    case BRnp:
      fprintf(theFile, "BRnp #%d", IMM);
      return;
    case BRnz:
      fprintf(theFile, "BRnz #%d", IMM);
      return;
    case BRnzp:
      fprintf(theFile, "BRnzp #%d", IMM);
      return;
    case ADD:
      fprintf(theFile, "ADD R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case MUL:
      fprintf(theFile, "MUL R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case SUB:
      fprintf(theFile, "SUB R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case DIV:
      fprintf(theFile, "DIV R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case ADDI:
      fprintf(theFile, "ADD R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case MOD:
      fprintf(theFile, "MOD R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case AND:
      fprintf(theFile, "AND R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case NOT:
      fprintf(theFile, "NOT R%d, R%d", Rd, Rs);
      return;
    case OR:
      fprintf(theFile, "OR R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case XOR:
      fprintf(theFile, "XOR R%d, R%d, R%d", Rd, Rs, Rt);
      return;
    case ANDI:
      fprintf(theFile, "AND R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case LDR:
      fprintf(theFile, "LDR R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case STR:
      fprintf(theFile, "STR R%d, R%d, #%d", Rt, Rs, IMM);
      return;
    case CONST:
      fprintf(theFile, "CONST R%d, #%d", Rd, IMM);
      return;
    case HICONST:
      fprintf(theFile, "HICONST R%d, #%d", Rd, IMM);
      return;
    case CMP:
      fprintf(theFile, "CMP R%d, R%d", Rs, Rt);
      return;
    case CMPU:
      fprintf(theFile, "CMPU R%d, R%d", Rs, Rt);
      return;
    case CMPI:
      fprintf(theFile, "CMPI R%d, #%d", Rs, IMM);
      return;
    case CMPIU:
      fprintf(theFile, "CMPIU R%d, #%d", Rs, IMM);
      return;
    case SLL:
      fprintf(theFile, "SLL R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case SRA:
      fprintf(theFile, "SRA R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case SRL:
      fprintf(theFile, "SRL R%d, R%d, #%d", Rd, Rs, IMM);
      return;
    case JSRR:
      fprintf(theFile, "JSRR R%d", Rs);
      return;
    case JSR:
      fprintf(theFile, "JSR #%d", IMM);
      return;
    case JMPR:
      fprintf(theFile, "JMPR R%d", Rs);
      return;
    case JMP:
      fprintf(theFile, "JMP #%d", IMM);
      return;
    case TRAP:
      fprintf(theFile, "TRAP #%d", IMM);
      return;
    case RTI:
      fprintf(theFile, "RTI");
      return;
    default:
      return;
  }
}