#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int isEmpty(stack *s) {
  if (!s) return 1;
  else return 0;
}

int stackSize(stack *s) {
  stack *temp = s;
  int counter = 0;
  while (temp) {
    counter++;
    temp = s->next;
  }
  return counter;
}

stack *initStack(int t) {
  stack *new_stack = malloc(sizeof(stack));
  if (!new_stack) {
    printf("Couldn't allocate space for a new Stack\n");
    exit(EXIT_FAILURE);
  }
  new_stack->next = NULL;
  new_stack->data = t;
  new_stack->pair = 0;
  return new_stack;
}

stack *push(stack *s, int t) {
  stack *new_stack = initStack(t);
  new_stack->next = s;
  return new_stack;
}

stack *pop(stack *s) {
  stack *next_stack = s->next;
  free(s);
  return next_stack;
}

stack *dup(stack *s) {
  int temp = s->data;
  return push(s, temp);
}

stack *swap(stack *s) {
  stack *first = s;
  stack *second = s->next;
  first->next = second->next;
  second->next = first;
  return second;
}

stack *clear(stack *s) {
  while (!isEmpty(s)) s = pop(s);
  return s;
}

void printStack(stack *s) {
  int val;
  if (s) {
    val = s->data;
    printf("%d\n", val);
  }
}