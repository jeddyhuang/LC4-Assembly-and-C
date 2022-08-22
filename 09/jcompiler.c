#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "tokenwriter.h"

int main(int argc, char **argv) {
  FILE *input;
  FILE *output;
  token *theToken;
  char *filename;
  char *temp;
  char *line;
  char *currtoken;
  int i;
  
  if(argc != 2) {
    printf("Incorrect Inputs\n");
    exit(EXIT_FAILURE);
  }
  
  filename = calloc(strlen(argv[1]) + 3, sizeof(char));
  strncpy(filename, argv[1], strlen(argv[1]) - 2);
  strcat(filename, ".asm");
  
  input = fopen(argv[1], "r");
  if(input == NULL) {
    printf("Error Reading File\n");
    free(filename);
    exit(EXIT_FAILURE);
  }
  
  output = fopen(filename, "w");
  if(output == NULL) {
    printf("Error Writing to File\n");
    free(input);
    free(filename);
    exit(EXIT_FAILURE);
  }
  free(filename);
  
  line = malloc(sizeof(char) * 500);
  while(!feof(input)) {
    fgets(line, 500, input);
    for(i = strcspn(line, ";"); i < strlen(line); i++) line[i] = '\0';
    currtoken = strtok(line, "\n\t ");
    while(currtoken != NULL) {
      theToken = malloc(sizeof(token));
      if(read_token(theToken, currtoken) == 1) {
        printf("Error Reading Token\n");
        print_token(theToken);
        free(theToken);
        free(line);
        free(input);
        free(output);
        exit(EXIT_FAILURE);
      }
      if(write_token(theToken, output) == 1) {
        printf("Error Writing Token\n");
        print_token(theToken);
        free(theToken);
        free(line);
        free(input);
        free(output);
        exit(EXIT_FAILURE);
      }
      free(theToken);
      currtoken = strtok(NULL, "\n\t ");
    }
  }
  free(line);
  fclose(input);
  fclose(output);
  return 1;
}