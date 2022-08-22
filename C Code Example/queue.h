#include <stdbool.h>

// Queue is a queue that stores integers that is
// implmented with a singly linked list
// a user can create a queue, add integers to the end,
// remove integers from the front, clear the queue,
// and print all values in it.

typedef struct queue_node_st {
  int val;
  struct queue_node_st *next;
} Queue_Node;

typedef struct queue_st {
  Queue_Node *first, *last;
} Queue;

// Normally it is good practice to have comments
// in here to explain the behaviour of each function
void Queue_Init(Queue *q);

void Queue_Add(Queue *q, int val);

bool Queue_Remove(Queue *q);

void Queue_Clear(Queue *q);

void Queue_Print(Queue *q);
