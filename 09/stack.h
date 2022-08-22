typedef struct stack_node {
  int data;
  int pair;
  struct stack_node *next;
} stack;

int isEmpty(stack *s);

int stackSize(stack *s);

stack *initStack(int t);

stack *push(stack *s, int t);

stack *pop(stack *s);

stack *dup(stack *s);

stack *swap(stack *s);

stack *clear(stack *s);

void printStack(stack *s);