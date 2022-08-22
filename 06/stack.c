#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int Stack_Empty(Stack *s) {
  if (!s) return 1;
  else return 0;
}

int Stack_Size(Stack *s) {
  Stack *temp = s;
  int counter = 0;
  while (temp) {
    counter++;
    temp = s->next;
  }
  return counter;
}

Stack *Stack_Init(Tuple *t) {
  Stack *new_stack = malloc(sizeof(Stack));
  if (!new_stack) {
    printf("Couldn't allocate space for a new Stack\n");
    exit(EXIT_FAILURE);
  }
  new_stack->next = NULL;
  new_stack->data = t;
  return new_stack;
}

Tuple *Tuple_Init(int n, int d) {
  Tuple *new_tuple = malloc(sizeof(Tuple));
  if (!new_tuple) {
    printf("Couldn't allocate space for a new Tuple\n");
    exit(EXIT_FAILURE);
  }
  new_tuple->num = n;
  new_tuple->den = d;
  return new_tuple;
}

Stack *Stack_Push(Stack *s, Tuple *t) {
  Stack *new_stack = Stack_Init(t);
  new_stack->next = s;
  return new_stack;
}

Stack *Stack_Add(Stack *s, int n, int d) {
  Tuple *temp = Tuple_Init(n, d);
  return Stack_Push(s, temp);
}

Stack *Stack_Pop(Stack *s) {
  Stack *next_stack = s->next;
  free(s->data);
  free(s);
  return next_stack;
}

Stack *Stack_Dup(Stack *s) {
  int num = s->data->num;
  int den = s->data->den;
  Tuple *new_tuple = Tuple_Init(num, den);
  new_tuple->num = num;
  new_tuple->den = den;
  return Stack_Push(s, new_tuple);
}

Stack *Stack_Swap(Stack *s) {
  Stack *first = s;
  Stack *second = s->next;
  first->next = second->next;
  second->next = first;
  return second;
}

Stack *Stack_Clear(Stack *s) {
  while (!Stack_Empty(s)) s = Stack_Pop(s);
  return s;
}

void Stack_Print(Stack *s) {
  int num, den;
  if (s) {
    num = s->data->num;
    den = s->data->den;
    printf("%d/%d\n", num, den);
  }
}