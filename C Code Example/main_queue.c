/*
 * main_queue.c
 */
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 200

int main () {
  char input[MAX_LINE_LENGTH];
  int value;
  Queue the_queue;

  Queue_Init(&the_queue);
  
  while (1) {
    printf ("Enter command (add, delete, list quit) : \n");

    fgets (input, MAX_LINE_LENGTH, stdin);

    // Check for add command
    if (sscanf (input, "add %d", &value) == 1) {
      Queue_Add(&the_queue, value);
      Queue_Print(&the_queue);
    }

    // Should probably do a better check 
    // for comannds using strcmp()

    // Check for delete command
    if (input[0] == 'd') {
      Queue_Remove(&the_queue);
      Queue_Print(&the_queue);
    }

    // Check for list command
    if (input[0] == 'l') {
      Queue_Print(&the_queue);
    }

    // check for quit command
    if (input[0] == 'q') {
      Queue_Clear(&the_queue);
      break;
    }
  }
  
  return 0;
}
