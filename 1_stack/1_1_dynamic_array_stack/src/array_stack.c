#include "array_stack.h"
#include <stdlib.h>

#define ARRAY_SIZE 10

Stack *create_stack() {
  Stack *stack = (Stack *)malloc(sizeof(Stack));
  stack->count = 0;
  stack->capacity = ARRAY_SIZE;
  stack->array = (Node *)malloc(sizeof(Node) * ARRAY_SIZE);
  return stack;
};

void push(Stack *stack, void *input) {
  if (stack->count == stack->capacity) {
    stack->array =
        realloc(stack->array, sizeof(Node) * (stack->capacity + ARRAY_SIZE));
  }

  stack->array[stack->count].data = input;
  stack->count++;
};

int pop(Stack *stack, void **output) {
  if (stack->count <= 0) {
    return 0;
  }
  stack->count--;
  *output = stack->array[stack->count].data;

  return 1;
};