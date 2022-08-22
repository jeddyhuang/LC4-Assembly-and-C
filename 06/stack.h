#ifndef STACK_H
#define STACK_H

typedef struct tuple {
  int num, den;
} Tuple;

typedef struct stack_node {
  Tuple *data;
  struct stack_node *next;
} Stack;

int Stack_Empty(Stack *s);

int Stack_Size(Stack *s);

Stack *Stack_Init(Tuple *t);

Tuple *Tuple_Init(int n, int d);

Stack *Stack_Push(Stack *s, Tuple *t);

Stack *Stack_Add(Stack *s, int n, int d);

Stack *Stack_Pop(Stack *s);

Stack *Stack_Dup(Stack *s);

Stack *Stack_Swap(Stack *s);

Stack *Stack_Clear(Stack *s);

void Stack_Print(Stack *s);

#endif