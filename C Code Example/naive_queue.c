#include <stdio.h>

typedef struct node_st {
  struct node_st* next;
  int val;
} Node;


int main() {
  Node first;
  // Node second
  // Node ...
  Node last;

  first.val = 2;
  first.next = &last;

  last.val = 0;
  last.next = NULL;

  // Iterate through the list
  Node *curr = &first;
  while(curr) {
    printf("%d\n", curr->val);
    curr = curr->next;
  }
}
