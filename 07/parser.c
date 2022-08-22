#include <stdio.h>
#include <stdlib.h>
#include "decode.h"
#include "loader.h"
#define ARRAY_SIZE 65536

int main(int argc, char **argv) {
  unsigned short int entries[ARRAY_SIZE];
  FILE *output_file;
  int i;
  INSN decoded;
  if (argc < 3) {
    printf("Incorrect Inputs");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < ARRAY_SIZE; i++) {
    entries[i] = 0;
  }
  for (i = 2; i < argc; i++) {
    ReadObjectFile(argv[i], entries);
  }
  output_file = fopen(argv[1], "w");
  if (output_file == NULL) {
    printf("Error Writing to File");
    exit(EXIT_FAILURE);
  }
  for (i = 0x0; i <= 0x1FFF; i++) {
    if (entries[i]!=0) {
      decoded = decode_insn(entries[i]);
      fprintf(output_file, "%04X : %04X -> ", i, entries[i]);
      print_insn(output_file, decoded);
      fprintf(output_file, "\n");
    }
  }
  for (i = 0x2000; i <= 0x7FFF; i++) {
    if (entries[i]!=0) {
      fprintf(output_file, "%04X : %04X\n", i, entries[i]);
    }
  }
  for (i = 0x8000; i <= 0x9FFF; i++) {
    if (entries[i]!=0) {
      decoded = decode_insn(entries[i]);
      fprintf(output_file, "%04X : %04X -> ", i, entries[i]);
      print_insn(output_file, decoded);
      fprintf(output_file, "\n");
    }
  }
  for (i = 0xA000; i <= 0xFFFF; i++) {
    if (entries[i]!=0) {
      fprintf(output_file, "%04X : %04X\n", i, entries[i]);
    }
  }
  fclose(output_file);
  return 1;
}