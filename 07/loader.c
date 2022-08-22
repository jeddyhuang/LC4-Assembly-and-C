#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

void ReadObjectFile (char *filename, unsigned short int *entries) {
  int byte1, byte2, section;
  unsigned short int data;
  int address, length, index;
  int i;
  FILE *input_file = fopen(filename, "r");
  if (input_file == NULL) {
    return;
  }
  while (1) {
    byte1 = fgetc(input_file);
    if (byte1 == EOF) {
      fclose(input_file);
      return;
    }
    byte2 = fgetc(input_file);
    section = (byte1 << 8) + byte2;
    
    switch (section) {
      case 0xCADE:
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        address = (byte1 << 8) + byte2;
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        length = (byte1 << 8) + byte2;
        for (i = 0; i < length; i++) {
          byte1 = fgetc(input_file);
          byte2 = fgetc(input_file);
          data = (byte1 << 8) + byte2;
          entries[address] = data;
          address++;
        }
        break;
      case 0xDADA:
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        address = (byte1 << 8) + byte2;
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        length = (byte1 << 8) + byte2;
        for (i = 0; i < length; i++) {
          byte1 = fgetc(input_file);
          byte2 = fgetc(input_file);
          data = (byte1 << 8) + byte2;
          entries[address] = data;
          address++;
        }
        break;
      case 0xC3B7:
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        address = (byte1 << 8) + byte2;
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        length = (byte1 << 8) + byte2;
        for (i = 0; i < length; i++) {
          byte1 = fgetc(input_file);
        }
        break;
      case 0xF17E:
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        length = (byte1 << 8) + byte2;
        for (i = 0; i < length; i++) {
          byte1 = fgetc(input_file);
        }
        break;
      case 0x715E:
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        address = (byte1 << 8) + byte2;
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        length = (byte1 << 8) + byte2;
        byte1 = fgetc(input_file);
        byte2 = fgetc(input_file);
        index = (byte1 << 8) + byte2;
        break;
      default:
        fclose(input_file);
        return;
    }
  }
}