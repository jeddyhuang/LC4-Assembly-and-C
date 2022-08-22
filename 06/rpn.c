#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#define MAX_INPUT_LENGTH 100

int gcd (int x, int y) {
  int a=abs(x), b=abs(y), temp;
  while (b) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}

int main () {
  char input[MAX_INPUT_LENGTH];
  char str1[MAX_INPUT_LENGTH];
  char str2[MAX_INPUT_LENGTH];
  
  Stack *stack = NULL;
  int i, size = 0;
  int num1, den1, num2, den2, number;
  
  while (1) {
    fgets (input, MAX_INPUT_LENGTH, stdin);
    
    for (i = 0; i < strlen(input); i++) {
      input[i] = tolower(input[i]);
    }
    
    if (sscanf(input, "%s %s", str1, str2) == 2) {
      printf("INVALID COMMAND\n");
    } else if (sscanf(input, "%d%s", &number, str1) == 1) {
      stack = Stack_Add(stack, number, 1);
      size++;
      Stack_Print(stack);
    } else if (sscanf(input, "%s", str1) == 1) {
      if (strcmp(str1, "+") == 0) {
        if (size >= 2) {
          num2 = stack->data->num;
          den2 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 *= den2;
          num2 *= den1;
          num1 += num2;
          den1 *= den2;
          den2 = gcd(num1, den1);
          num1 /= den2;
          den1 /= den2;
          stack = Stack_Add(stack, num1, den1);
          size--;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "-") == 0) {
        if (size >= 2) {
          num2 = stack->data->num;
          den2 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 *= den2;
          num2 *= den1;
          num1 -= num2;
          den1 *= den2;
          den2 = gcd(num1, den1);
          num1 /= den2;
          den1 /= den2;
          stack = Stack_Add(stack, num1, den1);
          size--;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "*") == 0) {
        if (size >= 2) {
          num2 = stack->data->num;
          den2 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 *= num2;
          den1 *= den2;
          den2 = gcd(num1, den1);
          num1 /= den2;
          den1 /= den2;
          stack = Stack_Add(stack, num1, den1);
          size--;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "/") == 0) {
        if (size >= 2) {
          num2 = stack->data->num;
          den2 = stack->data->den;
          stack = Stack_Pop(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          stack = Stack_Pop(stack);
          if (!num2) {
            stack = Stack_Clear(stack);
            printf("DIVIDE BY ZERO\n");
            exit(0);
          }
          num1 *= den2;
          den1 *= num2;
          den2 = gcd(num1, den1);
          num1 /= den2;
          den1 /= den2;
          if (den1 < 0) {
            num1 *= -1;
            den1 *= -1;
          }
          stack = Stack_Add(stack, num1, den1);
          size--;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "dup") == 0) {
        if (size >= 1) {
          stack = Stack_Dup(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          size++;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "swap") == 0) {
        if (size >= 2) {
          stack = Stack_Swap(stack);
          num1 = stack->data->num;
          den1 = stack->data->den;
          Stack_Print(stack);
        } else {
          printf("STACK ERROR\n");
        }
      } else if (strcmp(str1, "quit") == 0) {
        stack = Stack_Clear(stack);
        size = 0;
        exit(0);
      } else if (strcmp(str1, "drop") == 0) {
        if (size >= 1) {
          stack = Stack_Pop(stack);
          size--;
          Stack_Print(stack);
        }
      } else if (strcmp(str1, "clear") == 0) {
        stack = Stack_Clear(stack);
        size = 0;
      } else {
        printf("INVALID COMMAND\n");
      }
    }
  }
}