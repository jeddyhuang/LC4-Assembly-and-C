/*
 * queue.c
 */

#include <stdio.h>   // for printf
#include <stdlib.h>  // for malloc, free, and EXIT_FAILURE

#include "queue.h"

void Queue_Init(Queue *q) {
  q->first = NULL;
  q->last = NULL;
}

void Queue_Add(Queue *q, int val) {
  Queue_Node *node = malloc(sizeof(Queue_Node));

  if (node == NULL) {
    printf("Couldn't allocate space for a new Queue Node\n");
    exit(EXIT_FAILURE);
  }

  node->next = NULL;
  node->val = val;

  if (q->last) {  // equivalent to if (q->last != NULL) {
    q->last->next = node;
    q->last = node;
  } else {
    q->first = node;
    q->last = node;
  }
}

bool Queue_Remove(Queue *q) {
  if (!q->first) {  // equivalent to if(q->first == NULL)
    return false;
  }
  Queue_Node* next_first = q->first->next;

  if (q->last == q->first) {
    q->last = NULL;
    next_first = NULL;
  } else {
    next_first = q->first->next;
  }

  free(q->first);
  q->first = next_first;
  return true;
}

void Queue_Clear(Queue *q) {
  while(Queue_Remove(q));
}

void Queue_Print(Queue *q) {
  Queue_Node *curr = q->first;
  printf("\nQUEUE CONTAINS\n");
  while(curr) {
    printf("%d\n", curr->val);
    curr = curr->next;
  }
}
